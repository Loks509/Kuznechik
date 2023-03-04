#include "KuznShiphr.h"

KuznShiphr::KuznShiphr(unsigned char* _key)
{
    key.reserve(length_key);
    for (size_t i = 0; i < length_key; i++)
        key.push_back(_key[i]);
    tmp_key_1.resize(length_key / 2);
    tmp_key_2.resize(length_key / 2);
    create_table_Galua();
    fill_key();
}

KuznShiphr::~KuznShiphr()
{
}

unsigned char KuznShiphr::mult(unsigned char _a, unsigned char _b)
{
    unsigned char c = 0;
    int ind_a = 0, ind_b = 0;
    if (_a == 0 || _b == 0)
        return 0;

    for (size_t i = 0; (i < length_table_Galua) && (ind_a == 0 || ind_b == 0); i++)
    {
        if (table_Galua[i] == _a)
            ind_a = i;

        if (table_Galua[i] == _b)
            ind_b = i;
    }
    c = table_Galua[(ind_a + ind_b) % 255];
    return c;
}

void KuznShiphr::create_round_C(unsigned char* _c, int _begin) {
    _c[0] = _begin;
    l_transform(_c);
}

void KuznShiphr::s_transform(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
        _vec[i] = Pi[_vec[i]];
}

void KuznShiphr::s_transform_reverse(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
        _vec[i] = reverse_Pi[_vec[i]];
}

void KuznShiphr::l_transform(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
    {
        unsigned char tmp = 0;
        for (size_t j = 0; j < 16; j++)
        {
            tmp ^= mult(_vec[j], l_vec[j]);
        }
        for (size_t j = 0; j < 15; j++)
        {
            _vec[j] = _vec[j + 1];
        }
        _vec[15] = tmp;
    }
}

void KuznShiphr::l_transform_reverse(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
    {
        unsigned char tmp = 0;
        for (size_t j = 0; j < 16; j++)
        {
            tmp ^= mult(_vec[j], l_vec[15 - j]);
        }
        for (int j = 14; j >= 0; j--)
        {
            _vec[j + 1] = _vec[j];
        }
        _vec[0] = tmp;

    }
}

void KuznShiphr::xor_vec(unsigned char* _modable_vec, const unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
        _modable_vec[i] ^= _vec[i];
}

void KuznShiphr::create_round_key(const vector<unsigned char>& _in_key,
    vector<unsigned char>& _out_key,
    int _round) {
    _out_key = _in_key;
    for (size_t i = 0; i < 8; i++)
    {
        vector<unsigned char> round_C(16);
        for (size_t j = 0; j < 16; j++)
        {
            tmp_key_1[j] = _out_key[j];
            tmp_key_2[j] = _out_key[j + 16];
            _out_key[j + 16] = _out_key[j];
        }
        create_round_C(round_C.data(), _round * 8 + i + 1);
        xor_vec(tmp_key_1.data(), round_C.data());
        s_transform(tmp_key_1.data());
        l_transform(tmp_key_1.data());
        xor_vec(tmp_key_1.data(), tmp_key_2.data());
        for (size_t j = 0; j < 16; j++)
            _out_key[j] = tmp_key_1[j];
    }
}

void KuznShiphr::fill_key() {
    vector<unsigned char> local_key(key);

    arr_key.push_back(local_key);
    for (size_t i = 0; i < 4; i++)
    {
        create_round_key(local_key, local_key, i);
        arr_key.push_back(local_key);
    }
}

void KuznShiphr::split_key(vector<unsigned char>& _key_1,
    vector<unsigned char>& _key_2,
    const vector<unsigned char>& _from_key) {
    for (size_t i = 0; i < length_key / 2; i++)
    {
        _key_1[i] = _from_key[i];
        _key_2[i] = _from_key[i + length_key / 2];
    }
}

void KuznShiphr::create_table_Galua() {
    table_Galua.resize(length_table_Galua);
    table_Galua[0] = 1;
    int tmp;
    for (size_t i = 1; i < length_table_Galua; i++)
    {
        tmp = table_Galua[i - 1] * 2;
        if (tmp > 255) {
            tmp = tmp ^ 0b111000011 - 256;
        }
        table_Galua[i] = tmp;
    }
}

void KuznShiphr::encode(unsigned char* _data) {

    vector<unsigned char> key_1(length_key / 2);
    vector<unsigned char> key_2(length_key / 2);

    for (size_t round = 0; round < 5; round++)
    {
        split_key(key_1, key_2, arr_key[round]);
        xor_vec(_data, key_1.data());
        s_transform(_data);
        l_transform(_data);
        xor_vec(_data, key_2.data());
        if (round != 4) {
            s_transform(_data);
            l_transform(_data);
        }
    }
}

void KuznShiphr::decode(unsigned char* _data) {
    vector<unsigned char> key_1(length_key / 2);
    vector<unsigned char> key_2(length_key / 2);

    for (int round = 4; round >= 0; round--)
    {
        split_key(key_1, key_2, arr_key[round]);
        xor_vec(_data, key_2.data());
        l_transform_reverse(_data);
        s_transform_reverse(_data);
        xor_vec(_data, key_1.data());
        if (round != 0) {
            l_transform_reverse(_data);
            s_transform_reverse(_data);
        }
    }
}
