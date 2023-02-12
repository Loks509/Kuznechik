#pragma once
#include <iostream>
using namespace std;

void print_hex_vec2(unsigned char* c, int n) {
    for (size_t j = 0; j < n; j++)
    {
        printf(" %x ", c[j]);
    }
    cout << endl;
}

class KuznShiphr
{
public:
    KuznShiphr(unsigned char* key);
    ~KuznShiphr();

    void encode(unsigned char* data);
    void decode(unsigned char* data);
private:
    template<typename _Type>
    void CreateMatrix(int _I, int _J, _Type**& _A);

    template<typename _Type>
    void deleteMemory(int _I, _Type**& _A);

    unsigned char mult(unsigned char a, unsigned char b);
    void create_round_C(unsigned char* c, int begin);
    void s_transform(unsigned char* c);
    void s_transform_reverse(unsigned char* _vec);
    void l_transform(unsigned char* c);
    void l_transform_reverse(unsigned char* _vec);
    void xor_vec(unsigned char* key, unsigned char* C);
    void create_round_key(unsigned char* _in_key, unsigned char* _out_key, int _round);
    void fill_key();
    void copy_vec(unsigned char* from, unsigned char* to, int n);
    void get_keys12(unsigned char* key_1, unsigned char* key_2, unsigned char* from_key);

    void create_table_Galua();

    const unsigned char Pi[256] = {
        0xFC, 0xEE, 0xDD, 0x11, 0xCF, 0x6E, 0x31, 0x16,
        0xFB, 0xC4, 0xFA, 0xDA, 0x23, 0xC5, 0x04, 0x4D,
        0xE9, 0x77, 0xF0, 0xDB, 0x93, 0x2E, 0x99, 0xBA,
        0x17, 0x36, 0xF1, 0xBB, 0x14, 0xCD, 0x5F, 0xC1,
        0xF9, 0x18, 0x65, 0x5A, 0xE2, 0x5C, 0xEF, 0x21,
        0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F,
        0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0,
        0x06, 0x0B, 0xED, 0x98, 0x7F, 0xD4, 0xD3, 0x1F,
        0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB,
        0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC,
        0xB5, 0x70, 0x0E, 0x56, 0x08, 0x0C, 0x76, 0x12,
        0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87,
        0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7,
        0xF3, 0x91, 0x78, 0x6F, 0x9D, 0x9E, 0xB2, 0xB1,
        0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E,
        0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57,
        0xDF, 0xF5, 0x24, 0xA9, 0x3E, 0xA8, 0x43, 0xC9,
        0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03,
        0xE0, 0x0F, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC,
        0xDC, 0xE8, 0x28, 0x50, 0x4E, 0x33, 0x0A, 0x4A,
        0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44,
        0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41,
        0xAD, 0x45, 0x46, 0x92, 0x27, 0x5E, 0x55, 0x2F,
        0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B,
        0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7,
        0x30, 0x37, 0x6B, 0xE4, 0x88, 0xD9, 0xE7, 0x89,
        0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE,
        0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61,
        0x20, 0x71, 0x67, 0xA4, 0x2D, 0x2B, 0x09, 0x5B,
        0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52,
        0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0,
        0xD1, 0x66, 0xAF, 0xC2, 0x39, 0x4B, 0x63, 0xB6
    };

    const unsigned char reverse_Pi[256] = {
        0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0,
        0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
        0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18,
        0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
        0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4,
        0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
        0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9,
        0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
        0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B,
        0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
        0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F,
        0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
        0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2,
        0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
        0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11,
        0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
        0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F,
        0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
        0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1,
        0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
        0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0,
        0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
        0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D,
        0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
        0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67,
        0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
        0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88,
        0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
        0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE,
        0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
        0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7,
        0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74
    };

    const unsigned char l_vec[16] = {
        1, 148, 32, 133, 16, 194, 192, 1,
        251, 1, 192, 194, 16, 133, 32, 148
    };

    const int length_key = 32;

    const int length_data = 16;

    const int length_table_Galua = 256;

    unsigned char* key = nullptr;

    unsigned char* tmp_key_1 = nullptr;
    unsigned char* tmp_key_2 = nullptr;

    unsigned char** arr_key = nullptr;

    unsigned char* table_Galua = nullptr;

};

KuznShiphr::KuznShiphr(unsigned char* key)
{
    this->key = new unsigned char[this->length_key];
    this->copy_vec(key, this->key, this->length_key);
    this->tmp_key_1 = new unsigned char[this->length_key / 2];
    this->tmp_key_2 = new unsigned char[this->length_key / 2];
    this->create_table_Galua();
    cout << (int)(this->mult(148, 148)^32) << endl;
    /*for (size_t i = 0; i < 256; i++)
    {
        cout << (int)this->table_Galua[i] << "  ";
    }*/
}

KuznShiphr::~KuznShiphr()
{
    delete[] this->key;

    delete[] this->tmp_key_1;
    delete[] this->tmp_key_2;
    delete[] this->table_Galua;
    if (this->arr_key != nullptr)
        deleteMemory(5, this->arr_key);
}

template<typename _Type>
void KuznShiphr::CreateMatrix(int _I, int _J, _Type**& _A)
{
    int i1, i2;
    _A = new _Type * [_I];
    for (i1 = 0; i1 < _I; i1++) {
        _A[i1] = new _Type[_J];
        for (i2 = 0; i2 < _J; i2++) {
            _A[i1][i2] = 0.0;
        }
    }
}

template<typename _Type>
void KuznShiphr::deleteMemory(int _I, _Type**& _A) {
    int i1;
    for (i1 = 0; i1 < _I; i1++) {
        delete _A[i1];
    }
    delete[]_A;
}

unsigned char KuznShiphr::mult(unsigned char a, unsigned char b)
{
    unsigned char c = 0;
    int ind_a = 0, ind_b = 0;
    for (size_t i = 0; (i < this->length_table_Galua) && (ind_a == 0 || ind_b == 0); i++)
    {
        if (this->table_Galua[i] == a) 
            ind_a = i;

        if (this->table_Galua[i] == b)
            ind_b = i;
    }
    c = this->table_Galua[(ind_a + ind_b)%255];
    //unsigned char hi_bit;
    //int i;
    //for (i = 0; i < 8; i++)
    //{
    //    if (b & 1)
    //        c ^= a;
    //    hi_bit = a & 0x80;
    //    a <<= 1;
    //    if (hi_bit)
    //        a ^= 0xc3; // Полином x^8 + x^7 + x^6 + x + 1
    //    b >>= 1;
    //}
    return c;
}

void KuznShiphr::create_round_C(unsigned char* c, int begin) {
    c[0] = begin;
    this->l_transform(c);
}

void KuznShiphr::s_transform(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
        _vec[i] = this->Pi[_vec[i]];
}

void KuznShiphr::s_transform_reverse(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
        _vec[i] = this->reverse_Pi[_vec[i]];
}

void KuznShiphr::l_transform(unsigned char* _vec) {
    for (size_t i = 0; i < 16; i++)
    {
        unsigned char tmp = 0;
        for (size_t j = 0; j < 16; j++)
        {
            tmp ^= this->mult(_vec[j], l_vec[j]);
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
            tmp ^= this->mult(_vec[j], l_vec[15-j]);
        }
        for (int j = 14; j >=0; j--)
        {
            _vec[j + 1] = _vec[j];
        }
        _vec[0] = tmp;

    }
}

void KuznShiphr::xor_vec(unsigned char* key, unsigned char* C) {
    for (size_t i = 0; i < 16; i++)
        key[i] ^= C[i];
}

void KuznShiphr::create_round_key(unsigned char* _in_key, unsigned char* _out_key, int _round) {
    this->copy_vec(_in_key, _out_key, 32);
    for (size_t i = 0; i < 8; i++)
    {
        unsigned char round_C[16] = { 0 };
        for (size_t j = 0; j < 16; j++)
        {
            this->tmp_key_1[j] = _out_key[j];
            this->tmp_key_2[j] = _out_key[j + 16];
            _out_key[j + 16] = _out_key[j];
        }
        this->create_round_C(round_C, _round * 8 + i + 1);
        this->xor_vec(this->tmp_key_1, round_C);
        this->s_transform(this->tmp_key_1);
        this->l_transform(this->tmp_key_1);
        this->xor_vec(this->tmp_key_1, this->tmp_key_2);
        for (size_t j = 0; j < 16; j++)
            _out_key[j] = this->tmp_key_1[j];
    }
}

void KuznShiphr::fill_key() {
    if(this->arr_key == nullptr)
        this->CreateMatrix(5, this->length_key, this->arr_key);

    unsigned char* local_key = new unsigned char[this->length_key];
    this->copy_vec(this->key, local_key, this->length_key);
    this->copy_vec(local_key, this->arr_key[0], this->length_key);
    for (size_t i = 0; i < 4; i++)
    {
        create_round_key(local_key, local_key, i);
        this->copy_vec(local_key, this->arr_key[i+1], this->length_key);
    }
    delete[] local_key;
}

void KuznShiphr::copy_vec(unsigned char* from, unsigned char* to, int n) {
    for (size_t i = 0; i < n; i++)
        to[i] = from[i];
}

void KuznShiphr::get_keys12(unsigned char* key_1, unsigned char* key_2, unsigned char* from_key) {
    for (size_t i = 0; i < this->length_key/2; i++)
    {
        key_1[i] = from_key[i];
        key_2[i] = from_key[i + this->length_key / 2];
    }
}

void KuznShiphr::create_table_Galua() {
    this->table_Galua = new unsigned char[this->length_table_Galua];
    this->table_Galua[0]= 1;
    int tmp;
    for (size_t i = 1; i < this->length_table_Galua; i++)
    {
        tmp = this->table_Galua[i - 1] * 2;
        if (tmp > 255) {
            tmp = tmp ^ 0b111000011 - 256;
        }
        this->table_Galua[i] = tmp;
    }
}

void KuznShiphr::encode(unsigned char* data) {
    this->fill_key();

    unsigned char* key_1 = new unsigned char[this->length_key / 2];
    unsigned char* key_2 = new unsigned char[this->length_key / 2];
    
    for (size_t round = 0; round < 5; round++)
    {
        this->get_keys12(key_1, key_2, this->arr_key[round]);
        this->xor_vec(data, key_1);
        this->s_transform(data);
        this->l_transform(data);
        this->xor_vec(data, key_2);
        if (round != 4) {
            this->s_transform(data);
            this->l_transform(data);
        }
    }
    delete[] key_1;
    delete[] key_2;
}

void KuznShiphr::decode(unsigned char* data) {
    this->fill_key();

    unsigned char* key_1 = new unsigned char[this->length_key / 2];
    unsigned char* key_2 = new unsigned char[this->length_key / 2];

    for (int round = 4; round >=0; round--)
    {
        this->get_keys12(key_1, key_2, this->arr_key[round]);
        this->xor_vec(data, key_2);
        this->l_transform_reverse(data);
        this->s_transform_reverse(data);
        this->xor_vec(data, key_1);
        if (round != 0) {
            this->l_transform_reverse(data);
            this->s_transform_reverse(data);
        }
    }
    delete[] key_1;
    delete[] key_2;
}
