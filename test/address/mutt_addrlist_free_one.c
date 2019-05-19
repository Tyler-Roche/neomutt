/**
 * @file
 * Test code for mutt_addrlist_free_one()
 *
 * @authors
 * Copyright (C) 2019 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define TEST_NO_MAIN
#include "acutest.h"
#include "config.h"
#include "mutt/mutt.h"
#include "address/lib.h"
#include "common.h"

void test_mutt_addrlist_free_one(void)
{
  // void mutt_addrlist_free_one(struct AddressList *al, struct Address *a);

  {
    struct Address a = { 0 };
    mutt_addrlist_free_one(NULL, &a);
    TEST_CHECK_(1, "mutt_addrlist_free_one(NULL, &a)");
  }

  {
    struct AddressList al = { 0 };
    mutt_addrlist_free_one(&al, NULL);
    TEST_CHECK_(1, "mutt_addrlist_free_one(&al, NULL)");
  }

  {
    struct AddressList al = TAILQ_HEAD_INITIALIZER(al);
    const char *some_addresses =
        "john@doe.org, test@example.com, John Doe <john@doe.org>, "
        "foo@bar.baz, Another <john@doe.org>, foo@baz.info";
    int parsed = mutt_addrlist_parse(&al, some_addresses);
    TEST_CHECK(parsed == 6);
    struct Address *a = mutt_addr_new();
    a->personal = mutt_str_strdup("Another");
    a->mailbox = mutt_str_strdup("john@doe.org");
    mutt_addrlist_append(&al, a);
    TEST_CHECK(TAILQ_LAST(&al, AddressList) == a);
    parsed = mutt_addrlist_parse(&al, some_addresses);
    TEST_CHECK(parsed == 6);
    mutt_addrlist_free_one(&al, a);
    a = TAILQ_FIRST(&al);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("test@example.com", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("foo@bar.baz", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("foo@baz.info", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("test@example.com", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("foo@bar.baz", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("john@doe.org", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK_STR_EQ("foo@baz.info", a->mailbox);
    a = TAILQ_NEXT(a, entries);
    TEST_CHECK(a == NULL);
  }
}
