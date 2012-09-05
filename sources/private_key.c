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

#define PRIVATE
#include <tor/private_key.h>
#undef PRIVATE

#include <stdbool.h>
#include <assert.h>

TorPrivateKey*
tor_private_key_new (void)
{
	TorPrivateKey* self = malloc(sizeof(TorPrivateKey));

	self->references = 0;
	self->key        = RSA_new();

	assert(self->key);

	return self;
}

TorPrivateKey*
tor_private_key_new_from (RSA* key)
{
	TorPrivateKey* self = malloc(sizeof(TorPrivateKey));

	self->references = 0;
	self->key        = key;

	assert(self->key);

	return self;
}

TorPrivateKey*
tor_private_key_clone (TorPrivateKey* self)
{
	assert(self);

	self->references++;

	return self;
}

void
tor_private_key_destroy (TorPrivateKey* self)
{
	assert(self);

	if (--self->references > 0) {
		return;
	}

	assert(self->references <= 0);

	RSA_free(self->key);
	free(self);
}

EVP_PKEY*
tor_private_key_to_evp (TorPrivateKey* self)
{
	RSA*      tmp    = NULL;
	EVP_PKEY* result = NULL;

	assert(self);
	assert(self->key);

	if (!(tmp = RSAPrivateKey_dup(self->key))) {
		goto error;
	}

	if (!(result = EVP_PKEY_new())) {
		goto error;
	}

	if (!EVP_PKEY_assign_RSA(result, tmp)) {
		goto error;
	}

	return result;

error:
	if (tmp) {
		RSA_free(tmp);
	}

	if (result) {
		EVP_PKEY_free(result);
	}

	return NULL;
}
