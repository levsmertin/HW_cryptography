#include "mpirxx.h"
#include "mpir.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <winsock.h>
#include <sstream>
#include <string>
#include <vector>
#include "MyFile.h"

#define PORT 65000
#define SERVER "127.0.0.1" 





int main()
{

	bool flag_server = false;
	srand(time(0));
	std::stringstream ss;
	int size;
	char buff[1024];
	WSAStartup(0x0202, (WSADATA *)&buff[0]);
	SOCKET mysocket;
	mysocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in d_addr;
	d_addr.sin_family = AF_INET;
	d_addr.sin_port = htons(PORT);
	HOSTENT *hst;
	if (inet_addr(SERVER) != INADDR_NONE)
	{
		d_addr.sin_addr.s_addr = inet_addr(SERVER);
	}
	else
	{
		if (hst = gethostbyname(SERVER))
		{
			((unsigned long *)&d_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
		}
	}

	if (connect(mysocket, (sockaddr *)&d_addr, sizeof(d_addr)))
	{
		std::cout << "client2 offline" << std::endl;
		flag_server = true;
	}

	if (!flag_server)
	{
		std::cout << "client2 online" << std::endl;
		std::cout << std::endl;
		gmp_randstate_t state;
		mp_bitcnt_t init = rand() % 100;
		gmp_randinit_lc_2exp_size(state, init);
		int size;
		size = recv(mysocket, &buff[0], sizeof(buff), 0);
		mpz_t p;
		mpz_init_set_str(p, buff, 10);
		std::cout << "p: " << p << std::endl;
		size = recv(mysocket, &buff[0], sizeof(buff), 0);
		mpz_t n;
		mpz_init_set_str(n, buff, 10);
		std::cout << "N: " << n << std::endl;
		mpz_t B;
		std::cout << "Get B from client2" << std::endl;
		size = recv(mysocket, &buff[0], sizeof(buff), 0);
		mpz_init_set_str(B, buff, 10);
		std::cout << "B: " << B << std::endl;
		mpz_t a;
		mpz_init(a);
		mpz_urandomb(a, state, 64);
		mpz_t A;
		mpz_init(A);
		mpz_powm(A, p, a, n);
		ss.str(std::string());
		ss << A;
		std::cout << "Send A to client2" << std::endl;
		send(mysocket, ss.str().c_str(), sizeof(ss.str()), 0);
		std::cout << "A: " << A << std::endl;
		mpz_t KA;
		mpz_init(KA);
		mpz_powm(KA, B, a, n);
		std::cout << "Key : " << std::hex << KA << std::endl;
		uint64_t key;
		key = mpz_get_si(KA);
		std::vector <byte> cipher;
		std::vector <byte> plain;
		size = recv(mysocket, &buff[0], sizeof(buff), 0);
		cipher.resize(size);
		memcpy(cipher.data(), &buff[0], size);
		plain = D(cipher, key);
		std::cout << std::endl;
		for (int i = 0; i < plain.size(); i++)
		{
			std::cout << plain[i];
		}
		std::cout << std::endl;
		system("pause");

	}
	else
	{

		mysocket = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in local_addr;
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = htons(PORT);
		local_addr.sin_addr.s_addr = 0;
		bind(mysocket, (sockaddr *)&local_addr, sizeof(local_addr));
		listen(mysocket, 0x100);
		SOCKET client_socket;
		sockaddr_in client_addr;
		int client_addr_size = sizeof(client_addr);
		while ((client_socket = accept(mysocket, (sockaddr *)&client_addr, &client_addr_size)))
		{
			system("cls");
			std::cout << "client2 online" << std::endl;
			gmp_randstate_t state;
			mp_bitcnt_t init = rand() % 100;
			gmp_randinit_lc_2exp_size(state, init);
			mpz_t p;
			mpz_t n;
			mpz_t a;
			mpz_init(p);
			mpz_init(n);
			mpz_init(a);
			char buff[20 * 1024];
			mpz_urandomb(p, state, 64);
			mpz_urandomb(n, state, 64);
			ss.str(std::string());
			ss << p;
			std::cout << "p: " << ss.str() << std::endl;
			send(client_socket, ss.str().c_str(), sizeof(ss.str()), 0);
			ss.str(std::string());
			ss << n;
			std::cout << "N: " << ss.str() << std::endl;
			send(client_socket, ss.str().c_str(), sizeof(ss.str()), 0);
			mpz_urandomb(a, state, 64);
			mpz_t A;
			mpz_init(A);
			mpz_powm(A, p, a, n);
			ss.str(std::string());
			ss << A;
			std::cout << "Sending A to client2" << std::endl;
			send(client_socket, ss.str().c_str(), sizeof(ss.str()), 0);
			std::cout << "A: " << ss.str() << std::endl;
			mpz_t B;
			size = recv(client_socket, &buff[0], sizeof(buff), 0);
			mpz_init_set_str(B, buff, 10);
			std::cout << "Get B from client2: " << B << std::endl;
			mpz_t KA;
			mpz_init(KA);
			mpz_powm(KA, B, a, n);
			std::cout << "Key : " << std::hex << KA << std::endl;

			uint64_t key;
			key = mpz_get_si(KA);
			std::vector <byte> cipher;
			std::vector <byte> plain;
			byte plain_b[] = "Hello Friend";
			plain.resize(sizeof (plain));
			memcpy(plain.data(), plain_b, sizeof(plain_b));
			cipher = E(plain, key);
			send(client_socket, (const char *)cipher.data(), cipher.size(), 0);
			closesocket(client_socket);
			system("pause");

		}
	}
}