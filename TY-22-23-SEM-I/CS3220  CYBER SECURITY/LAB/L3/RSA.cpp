#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;
using namespace std;

// class for RSA_CRYPTOSYSTEM
class RSA_CRYPTOSYSTEM
{
public:
    unsigned p;       // 1st prime number
    unsigned q;       // 2nd prime number
    unsigned num;     // p*q
    unsigned phi_num; //(p-1)*(q-1) = Φ(n)
    unsigned pub_e;   // 1 < e < phi_n and gcd(e,phi_n) = 1 (public_key)
    unsigned pri_d;   // e*d mod phi_n = 1 (private_key)
    unsigned message; // secret message (plain_text)

    boost::multiprecision::cpp_int plain_text;
    boost::multiprecision::cpp_int cipher_text;

    void start();
    void check_valid_prime();
    unsigned n();
    unsigned phi_n();
    unsigned e();
    unsigned d();
    unsigned d(unsigned encry);
    unsigned e(unsigned decry);

    void calculate_both();
    void calculate_private();
    void calculate_public();

    boost::multiprecision::cpp_int encrypt(unsigned message);
    boost::multiprecision::cpp_int decrypt();
};

// Enter the prime Numbers:
void RSA_CRYPTOSYSTEM::start()
{
    cout << "Enter 1st Prime Number: " << endl;
    cin >> p;

    cout << "Enter 2st Prime Number: " << endl;
    cin >> q;
}

// Validating the prime Numbers:
void RSA_CRYPTOSYSTEM::check_valid_prime()
{
    vector<unsigned> p_factor;
    for (int i = 2; i <= static_cast<unsigned>(sqrt(p)); i++)
    {
        if (p % i == 0)
        {
            p_factor.push_back(i);
            p_factor.push_back(p / i);
        }
    }
    vector<unsigned> q_factor;
    for (int i = 2; i <= static_cast<unsigned>(sqrt(q)); i++)
    {
        if (q % i == 0)
        {
            q_factor.push_back(i);
            q_factor.push_back(p / i);
        }
    }
    if (p_factor.size() != 0 || q_factor.size() != 0)
    {
        throw(runtime_error("non prime numbers!"));
    }
}

// calculating the value for n:
unsigned RSA_CRYPTOSYSTEM::n()
{
    num = p * q;
    return num;
}

// calculating the value for Φ(n):
unsigned RSA_CRYPTOSYSTEM::phi_n()
{
    phi_num = (p - 1) * (q - 1);
    return phi_num;
}

// calculating the value for Public Key i.e. 'e':
unsigned RSA_CRYPTOSYSTEM::e()
{
    unsigned i = 2;
    while (gcd(i, phi_num) != 1)
        i++;
    pub_e = i;
    if (pub_e >= phi_num)
        throw(runtime_error("Value for e is greater than and equal to value of phi n"));
    return pub_e;
}

unsigned RSA_CRYPTOSYSTEM::e(unsigned decry)
{
    unsigned k = 1;
    while (((k * phi_num) + 1) % decry != 0)
        k++;
    pub_e = ((k * phi_num) + 1) / decry;
    return pub_e;
}

// calculating the value for Private Key i.e. 'd':
unsigned RSA_CRYPTOSYSTEM::d()
{
    unsigned k = 1;
    while (((k * phi_num) + 1) % pub_e != 0)
        k++;
    pri_d = ((k * phi_num) + 1) / pub_e;
    return pri_d;
}

unsigned RSA_CRYPTOSYSTEM::d(unsigned encry)
{
    unsigned k = 1;
    while (((k * phi_num) + 1) % encry != 0)
        k++;
    pri_d = ((k * phi_num) + 1) / encry;
    return pri_d;
}

// Encryption:
boost::multiprecision::cpp_int RSA_CRYPTOSYSTEM::encrypt(unsigned message)
{
    cipher_text = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(message), pub_e))) % num;
    return cipher_text;
}

// Decryption:
boost::multiprecision::cpp_int RSA_CRYPTOSYSTEM::decrypt()
{
    plain_text = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(cipher_text), pri_d))) % num;
    return plain_text;
}

// Operations:
void RSA_CRYPTOSYSTEM::calculate_both()
{
    start();
    check_valid_prime();
    cout << "Value of N: " << n() << endl;
    cout << "Value of Φ(n): " << phi_n() << endl;
    cout << "Value of e(Public Key): " << e() << endl;
    cout << "Value of d(Private Key): " << d() << endl;
    cout << "Enter Message which you want to Encrypt:" << endl;
    cin >> message;
    cout << "Encrypted Message: " << encrypt(message) << endl;
    cout << "Decrypted Message: " << decrypt() << endl;
}

void RSA_CRYPTOSYSTEM::calculate_private()
{
    unsigned encry;
    start();
    check_valid_prime();
    cout << "Value of N: " << n() << endl;
    cout << "Value of Φ(n): " << phi_n() << endl;
    cout << "Enter Public Key: " << endl;
    cin >> pub_e;
    cout << "Value of d(Private Key): " << d(pub_e) << endl;
    cout << "Enter Message which you want to Encrypt:" << endl;
    cin >> message;
    cout << "Encrypted Message: " << encrypt(message) << endl;
}

void RSA_CRYPTOSYSTEM::calculate_public()
{
    unsigned decry;
    start();
    check_valid_prime();
    cout << "Value of N: " << n() << endl;
    cout << "Value of Φ(n): " << phi_n() << endl;
    cout << "Enter Private Key: " << endl;
    cin >> pri_d;
    cout << "Value of e(Public Key): " << e(pri_d) << endl;
    cout << "Enter Message which you want to Decrypt:" << endl;
    cin >> cipher_text;
    cout << "Decrypted Message: " << decrypt() << endl;
}

// main funtoin:
int main()
{
    try
    {
        RSA_CRYPTOSYSTEM RSA;
        int choice;
        cout << "1. Generate Public and Privare Key using Prime Number.\n2. Generate Private Key using Prime and Public Key.\n3. Generate Public Key using Prime and Private Key." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            RSA.calculate_both();
            break;
        case 2:
            RSA.calculate_private();
            break;
        case 3:
            RSA.calculate_public();
            break;

        default:
            cout << "Enter valid Choice!";
            break;
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
