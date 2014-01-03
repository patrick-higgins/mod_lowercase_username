/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "httpd.h"
#include "http_config.h"
#include "http_log.h"
#include "http_request.h"

module AP_MODULE_DECLARE_DATA lowercase_username_module;

static int fixup_user(request_rec *r) {
    if (r->user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                      "mod_lowercase_username: user is null");
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                  "mod_lowercase_username: original user %s",
                  r->user);

    ap_str_tolower(r->user);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r,
                  "mod_lowercase_username: lowercase user %s",
                  r->user);
    return DECLINED;
}

static void register_hooks(apr_pool_t *p) {
    ap_hook_fixups(fixup_user, NULL, NULL, APR_HOOK_LAST);
}

module AP_MODULE_DECLARE_DATA lowercase_username_module = {
    STANDARD20_MODULE_STUFF,
    NULL,          /* dir config creater */
    NULL,          /* dir merger --- default is to override */
    NULL,          /* server config */
    NULL,          /* merge server config */
    NULL,          /* command apr_table_t */
    register_hooks /* register hooks */
};
