/*
 *
 * Copyright 2019 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "asylo/identity/provisioning/sgx/internal/fake_sgx_pki.h"

#include <functional>
#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "absl/strings/string_view.h"
#include "absl/time/clock.h"
#include "absl/types/span.h"
#include "asylo/crypto/certificate.pb.h"
#include "asylo/crypto/certificate_interface.h"
#include "asylo/crypto/certificate_util.h"
#include "asylo/crypto/ecdsa_p256_sha256_signing_key.h"
#include "asylo/crypto/signing_key.h"
#include "asylo/crypto/x509_certificate.h"
#include "asylo/test/util/status_matchers.h"

namespace asylo {
namespace sgx {
namespace {

using ::testing::Ge;
using ::testing::Le;
using ::testing::TestWithParam;
using ::testing::Values;

// A test fixture for a single CertificateAndPrivateKey.
class FakeSgxPkiTest : public TestWithParam<const CertificateAndPrivateKey *> {
 protected:
  void SetUp() override {
    ASYLO_ASSERT_OK_AND_ASSIGN(certificate_, X509Certificate::CreateFromPem(
                                                 GetParam()->certificate_pem));
    ASYLO_ASSERT_OK_AND_ASSIGN(
        signing_key_,
        EcdsaP256Sha256SigningKey::CreateFromPem(GetParam()->signing_key_pem));
  }

  std::unique_ptr<CertificateInterface> certificate_;
  std::unique_ptr<SigningKey> signing_key_;
};

TEST_P(FakeSgxPkiTest, CertIsWithinValidityPeriod) {
  X509Validity validity;
  ASYLO_ASSERT_OK_AND_ASSIGN(
      validity,
      CHECK_NOTNULL(dynamic_cast<X509Certificate *>(certificate_.get()))
          ->GetValidity());
  EXPECT_THAT(absl::Now(), Ge(validity.not_before));
  EXPECT_THAT(absl::Now(), Le(validity.not_after));
}

TEST_P(FakeSgxPkiTest, CertsIsForVerifyingKeyOfGivenSigningKey) {
  std::unique_ptr<VerifyingKey> expected_subject_key;
  ASYLO_ASSERT_OK_AND_ASSIGN(expected_subject_key,
                             signing_key_->GetVerifyingKey());

  std::string subject_key_der;
  ASYLO_ASSERT_OK_AND_ASSIGN(subject_key_der, certificate_->SubjectKeyDer());
  std::unique_ptr<VerifyingKey> actual_subject_key;
  ASYLO_ASSERT_OK_AND_ASSIGN(
      actual_subject_key,
      EcdsaP256Sha256VerifyingKey::CreateFromDer(subject_key_der));

  EXPECT_TRUE(*actual_subject_key == *expected_subject_key);
}

INSTANTIATE_TEST_SUITE_P(AllCertsAndSigningKeys, FakeSgxPkiTest,
                         Values(&kFakeSgxRootCa, &kFakeSgxPlatformCa,
                                &kFakeSgxTcbSigner));

// A test fixture for a chain of CertificateAndPrivateKeys.
class FakeSgxPkiChainsTest
    : public TestWithParam<absl::Span<const CertificateAndPrivateKey *>> {
 protected:
  void SetUp() override {
    CertificateChain proto_chain;
    for (const CertificateAndPrivateKey *cert_and_key : GetParam()) {
      Certificate *certificate = proto_chain.add_certificates();
      certificate->set_format(Certificate::X509_PEM);
      certificate->set_data(cert_and_key->certificate_pem.data(),
                            cert_and_key->certificate_pem.size());
    }
    ASYLO_ASSERT_OK_AND_ASSIGN(
        chain_,
        CreateCertificateChain(
            {{Certificate::X509_PEM, X509Certificate::Create}}, proto_chain));
  }

  CertificateInterfaceVector chain_;
};

TEST_P(FakeSgxPkiChainsTest, ChainIsValid) {
  VerificationConfig config(/*all_fields=*/true);
  ASYLO_EXPECT_OK(VerifyCertificateChain(chain_, config));
}

const CertificateAndPrivateKey *kPlatformCaChain[] = {&kFakeSgxPlatformCa,
                                                      &kFakeSgxRootCa};
const CertificateAndPrivateKey *kTcbSignerChain[] = {&kFakeSgxTcbSigner,
                                                     &kFakeSgxRootCa};
INSTANTIATE_TEST_SUITE_P(AllChains, FakeSgxPkiChainsTest,
                         Values(absl::MakeSpan(kPlatformCaChain),
                                absl::MakeSpan(kTcbSignerChain)));

}  // namespace
}  // namespace sgx
}  // namespace asylo
