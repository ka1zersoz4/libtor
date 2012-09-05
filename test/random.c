/* Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of libtor - https://github.com/libtor/libtor
 *
 * libtor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * libtor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with libtor. If not, see <http://www.gnu.org/licenses/>.
 */

#include <tor/random.h>

void
test_random_int (void* data)
{
	tt_int_op(tor_random_int(10), <, 10);
	tt_int_op(tor_random_int(300), <, 300);
	tt_int_op(tor_random_int(100000), <, 100000);

end:;
}

struct testcase_t random_tests[] = {
	{ "int", test_random_int },

	END_OF_TESTCASES
};
