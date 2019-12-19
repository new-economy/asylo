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

namespace asylo {
namespace sgx {

const CertificateAndPrivateKey kFakeSgxRootCa = {
    R"pem(-----BEGIN CERTIFICATE-----
MIIChDCCAiugAwIBAgIVAKk7nb9ghovhxdr15DdJaAYcCOLtMAoGCCqGSM49BAMC
MIGNMTAwLgYDVQQDDCdBc3lsbyBGYWtlIFNHWCBSb290IENBIEZvciBUZXN0aW5n
IE9ubHkxLDAqBgNVBAoMI0FzeWxvIEZha2UgU0dYIFBLSSBGb3IgVGVzdGluZyBP
bmx5MREwDwYDVQQHDAhLaXJrbGFuZDELMAkGA1UECAwCV0ExCzAJBgNVBAYTAlVT
MB4XDTE5MDEwMTAwMDAwMFoXDTQ5MTIzMTIzNTk1OVowgY0xMDAuBgNVBAMMJ0Fz
eWxvIEZha2UgU0dYIFJvb3QgQ0EgRm9yIFRlc3RpbmcgT25seTEsMCoGA1UECgwj
QXN5bG8gRmFrZSBTR1ggUEtJIEZvciBUZXN0aW5nIE9ubHkxETAPBgNVBAcMCEtp
cmtsYW5kMQswCQYDVQQIDAJXQTELMAkGA1UEBhMCVVMwWTATBgcqhkjOPQIBBggq
hkjOPQMBBwNCAARK97DEsISoPNf/uASTz68CIjZ7YXxUyZbF1Qp57pSxUNufMy9i
jd5XzwpIEReZoB12O46+rA4+6Z2Jm77dMeIvo2YwZDAfBgNVHSMEGDAWgBTMhCIh
J51Yc8ZMc3DIDaONAESnXDAdBgNVHQ4EFgQUzIQiISedWHPGTHNwyA2jjQBEp1ww
DgYDVR0PAQH/BAQDAgEGMBIGA1UdEwEB/wQIMAYBAQECAQEwCgYIKoZIzj0EAwID
RwAwRAIgRre0NHzlp+vh/zYlnHGDQ0eOPtjfG6hzmf4Z8ciyuaoCICtA0lVm2GQB
zUf61sdGT+9NLBbB1f8ibdySIVujAmxv
-----END CERTIFICATE-----)pem",
    R"pem(-----BEGIN EC PRIVATE KEY-----
MHcCAQEEIMsbxXDTgZq6WPEGniqIUPQP/cn3IpX1Zb6EXx77vruUoAoGCCqGSM49
AwEHoUQDQgAESvewxLCEqDzX/7gEk8+vAiI2e2F8VMmWxdUKee6UsVDbnzMvYo3e
V88KSBEXmaAddjuOvqwOPumdiZu+3THiLw==
-----END EC PRIVATE KEY-----)pem",
};

const CertificateAndPrivateKey kFakeSgxPlatformCa = {
    R"pem(-----BEGIN CERTIFICATE-----
MIICijCCAi+gAwIBAgIVAKTjQPjvKF3h9ViZDZ5rQycoMCt2MAoGCCqGSM49BAMC
MIGNMTAwLgYDVQQDDCdBc3lsbyBGYWtlIFNHWCBSb290IENBIEZvciBUZXN0aW5n
IE9ubHkxLDAqBgNVBAoMI0FzeWxvIEZha2UgU0dYIFBLSSBGb3IgVGVzdGluZyBP
bmx5MREwDwYDVQQHDAhLaXJrbGFuZDELMAkGA1UECAwCV0ExCzAJBgNVBAYTAlVT
MB4XDTE5MDEwMTAwMDAwMFoXDTM0MDEwMTAwMDAwMFowgZExNDAyBgNVBAMMK0Fz
eWxvIEZha2UgU0dYIFBsYXRmb3JtIENBIEZvciBUZXN0aW5nIE9ubHkxLDAqBgNV
BAoMI0FzeWxvIEZha2UgU0dYIFBLSSBGb3IgVGVzdGluZyBPbmx5MREwDwYDVQQH
DAhLaXJrbGFuZDELMAkGA1UECAwCV0ExCzAJBgNVBAYTAlVTMFkwEwYHKoZIzj0C
AQYIKoZIzj0DAQcDQgAEaW/AhuvWCE54xAWzIFxQKH69Q9uFWEenMYClbz3YNNzT
EvRpjxZ5Kh3qv7yN3/lAfU80+xmlDpRcc0rRj+PMsqNmMGQwHwYDVR0jBBgwFoAU
zIQiISedWHPGTHNwyA2jjQBEp1wwHQYDVR0OBBYEFMcREC1SbTeykljun8DOLPkg
Jyd/MA4GA1UdDwEB/wQEAwIBBjASBgNVHRMBAf8ECDAGAQEBAgEAMAoGCCqGSM49
BAMCA0kAMEYCIQD3cdKDFlc7+mfwcylgrWfB3sOhxhZDC1aaetrmkVaUcQIhALZA
Yusgokb6YjEsH5V8hZ2MmKSJ5R0WC7kxq2yiNFPP
-----END CERTIFICATE-----)pem",
    R"pem(-----BEGIN EC PRIVATE KEY-----
MHcCAQEEII2c4/uWfsYpG8ioplhz6Ka2fVK4gTat5kRo4nIL65PeoAoGCCqGSM49
AwEHoUQDQgAEaW/AhuvWCE54xAWzIFxQKH69Q9uFWEenMYClbz3YNNzTEvRpjxZ5
Kh3qv7yN3/lAfU80+xmlDpRcc0rRj+PMsg==
-----END EC PRIVATE KEY-----)pem",
};

const CertificateAndPrivateKey kFakeSgxTcbSigner = {
    R"pem(-----BEGIN CERTIFICATE-----
MIICgTCCAiegAwIBAgIUVZNZVx55g09uske5m1G8nrhrjxEwCgYIKoZIzj0EAwIw
gY0xMDAuBgNVBAMMJ0FzeWxvIEZha2UgU0dYIFJvb3QgQ0EgRm9yIFRlc3Rpbmcg
T25seTEsMCoGA1UECgwjQXN5bG8gRmFrZSBTR1ggUEtJIEZvciBUZXN0aW5nIE9u
bHkxETAPBgNVBAcMCEtpcmtsYW5kMQswCQYDVQQIDAJXQTELMAkGA1UEBhMCVVMw
HhcNMTkwMTAxMDAwMDAwWhcNMjYwMTAxMDAwMDAwWjCBkDEzMDEGA1UEAwwqQXN5
bG8gRmFrZSBTR1ggVGNiIFNpZ25lciBGb3IgVGVzdGluZyBPbmx5MSwwKgYDVQQK
DCNBc3lsbyBGYWtlIFNHWCBQS0kgRm9yIFRlc3RpbmcgT25seTERMA8GA1UEBwwI
S2lya2xhbmQxCzAJBgNVBAgMAldBMQswCQYDVQQGEwJVUzBZMBMGByqGSM49AgEG
CCqGSM49AwEHA0IABCCFkejnokc+0MFTFYXWxUuRsvNVLYAQLWDyfTni2aAqJHv7
gty0bXfqYZZTdcBg8ZPvcgV9HStaUA6QmUT2AiujYDBeMB8GA1UdIwQYMBaAFMyE
IiEnnVhzxkxzcMgNo40ARKdcMB0GA1UdDgQWBBSKIpPrF/6+UEW7n0j4wEHFazDb
lTAOBgNVHQ8BAf8EBAMCB4AwDAYDVR0TAQH/BAIwADAKBggqhkjOPQQDAgNIADBF
AiAsh51FjwCbdMKe4T7HtXqRzmkRThNz0RxODIx6NL2OBwIhAKSVZdtc8YI3Kj4L
8rk1f1l/tWHqII6f5haKpYmOD6Cc
-----END CERTIFICATE-----)pem",
    R"pem(-----BEGIN EC PRIVATE KEY-----
MHcCAQEEINJielbvwI0VMyj4aDhKKbNYLvPKUazVXjzqZk9shGVjoAoGCCqGSM49
AwEHoUQDQgAEIIWR6OeiRz7QwVMVhdbFS5Gy81UtgBAtYPJ9OeLZoCoke/uC3LRt
d+phllN1wGDxk+9yBX0dK1pQDpCZRPYCKw==
-----END EC PRIVATE KEY-----)pem",
};

}  // namespace sgx
}  // namespace asylo
