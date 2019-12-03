#
# Copyright 2018 Asylo authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])  # Apache v2.0

# Contains internal libraries related to null identity and null assertion.

package(default_visibility = [
    "//asylo/identity/attestation/null:__subpackages__",
])

# Definition of a null assertion.
proto_library(
    name = "null_assertion_proto",
    srcs = ["null_assertion.proto"],
)

cc_proto_library(
    name = "null_assertion_cc_proto",
    visibility = ["//asylo/identity/null_identity:__subpackages__"],
    deps = [":null_assertion_proto"],
)