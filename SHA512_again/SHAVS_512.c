#define _CRT_SECURE_NO_WARNINGS
#include "sha512.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

void Ascii(char* string, unsigned char* stream, int* len)
{

	char seps[] = "=, , \t, \n";//���⼭ ����
	char *tok;

	unsigned char buf[102400] = { 0, };
	int i = 0, j = 0, cnt = 0, n = 0;
	unsigned char result = 0, six = 0;

	tok = strtok(string, seps);


	while (tok != NULL)
	{
		if (strstr(tok, "Len") == NULL && strstr(tok, "Msg") == NULL && strstr(tok, "Seed") == NULL)
		{
			*len = strlen(tok) / 2;

			while (j < strlen(tok))
			{
				result = 0;
				six = 0;

				for (i = j; i < j + 2; i++)
				{
					if (isalpha(tok[i]))
					{
						result = toupper(tok[i]) - 55;
						six = six * 16 + result;
					}
					else
					{
						result = tok[i] - 48;
						six = six * 16 + result;
					}
				}

				buf[n] = six;
				n++;
				j = j + 2;
			}
		}
		tok = strtok(NULL, seps);
	}

	memcpy(stream, buf, *len);

}


void Short_Messages_Test()
{
	FILE *fp_req;
	FILE *fp_fax;
	char L_buff[100];
	char Len_buff[1000];
	char Msg_buff[1000];
	char buf[1000];

	int i;
	int* Len_len, Msg_len;
	unsigned char L[100] = { 0, };
	unsigned char Len[1000] = { 0, };
	unsigned char Msg[1000] = { 0, };
	unsigned char pszDigest[1000] = { 0, };

	fp_req = fopen("SHA2(512)ShortMsg.req", "r");
	fp_fax = fopen("SHA2(512)ShortMsg.fax", "w");

	if (fp_req == NULL || fp_fax == NULL)
	{
		printf("���Ͽ��� ����\n");
		return;
	}

	fgets(L_buff, sizeof(L_buff), fp_req);
	printf("%s\n", L_buff);
	fputs(L_buff, fp_fax);
	fprintf(fp_fax, "\n");

	fgets(buf, sizeof(buf), fp_req);
	memset(buf, 0, sizeof(buf));

	while (fgets(Len_buff, sizeof(Len_buff), fp_req) != NULL)
	{
		/****************Len******************/
		printf("%s", Len_buff);
		fputs(Len_buff, fp_fax);
		memset(Len_buff, 0, sizeof(Len_buff));

		/****************Msg******************/
		fgets(Msg_buff, sizeof(Msg_buff), fp_req);
		printf("%s", Msg_buff);
		fputs(Msg_buff, fp_fax);
		Ascii(Msg_buff, Msg, &Msg_len);

		if (Msg[0] == 00)
		{
			Msg[0] = NULL;
			Msg_len = 0;
		}

		memset(Msg_buff, 0, sizeof(Msg_buff));

		/*****************Enter***************/
		fgets(buf, sizeof(buf), fp_req);
		memset(buf, 0, sizeof(buf));

		/*****************Enc***************/
		SHA512(Msg, Msg_len, pszDigest);

		/*****************MD***************/
		printf("MD = ");
		for (i = 0; i < 64; i++)
		{
			printf("%02X", pszDigest[i]);
		}
		printf("\n");
		printf("\n");

		//���Ͽ� ���ֱ�
		fprintf(fp_fax, "MD = ");
		for (i = 0; i < 64; i++)
		{
			fprintf(fp_fax, "%02X", pszDigest[i]);
		}
		fprintf(fp_fax, "\n");
		fprintf(fp_fax, "\n");
	}
	fclose(fp_req);
	fclose(fp_fax);
}

void Long_Messages_Test()
{
	FILE *fp_req;
	FILE *fp_fax;
	char L_buff[1000] = { 0, };
	char Len_buff[1000] = { 0, };
	char Msg_buff[102400] = { 0, };
	char buf[1000] = { 0, };

	int i;
	int* Len_len, Msg_len;

	char* Len_string, Msg_string;
	unsigned char L[1000] = { 0, };
	unsigned char Len[1000] = { 0, };
	unsigned char Msg[102400] = { 0, };
	unsigned char pszDigest[1000] = { 0, };

	fp_req = fopen("SHA2(512)LongMsg.req", "r");
	fp_fax = fopen("SHA2(512)LongMsg.fax", "w");

	if (fp_req == NULL || fp_fax == NULL)
	{
		printf("���Ͽ��� ����\n");
		return;
	}

	fgets(L_buff, sizeof(L_buff), fp_req);
	printf("%s", L_buff);
	fputs(L_buff, fp_fax);
	fprintf(fp_fax, "\n");

	fgets(buf, sizeof(buf), fp_req);
	memset(buf, 0, sizeof(buf));

	while (fgets(Len_buff, sizeof(Len_buff), fp_req) != NULL)
	{
		/****************Len******************/
		printf("%s", Len_buff);
		fputs(Len_buff, fp_fax);
		memset(Len_buff, 0, sizeof(Len_buff));

		/****************Msg******************/
		fgets(Msg_buff, sizeof(Msg_buff), fp_req);
		printf("%s", Msg_buff);
		fputs(Msg_buff, fp_fax);
		Ascii(Msg_buff, Msg, &Msg_len);
		memset(Msg_buff, 0, sizeof(Msg_buff));

		/*****************Enter***************/
		fgets(buf, sizeof(buf), fp_req);
		memset(buf, 0, sizeof(buf));

		/*****************Enc***************/
		SHA512(Msg, Msg_len, pszDigest);

		/*****************MD***************/
		printf("MD = ");
		for (i = 0; i < 64; i++)
		{
			printf("%02X", pszDigest[i]);
		}
		printf("\n");
		printf("\n");

		//���Ͽ� ���ֱ�
		fprintf(fp_fax, "MD = ");
		for (i = 0; i < 64; i++)
		{
			fprintf(fp_fax, "%02X", pszDigest[i]);
		}
		fprintf(fp_fax, "\n");
		fprintf(fp_fax, "\n");
	}
	fclose(fp_req);
	fclose(fp_fax);
}

void Pseudorandomly_Generated_Messages_Test()
{
	FILE *fp_req;
	FILE *fp_fax;
	char L_buff[1000] = { 0, };
	char Seed_buff[1000] = { 0, };
	char buf[1000] = { 0, };

	int i, j, n;
	int Seed_len, L_len;

	char* Seed_string;
	unsigned char L[1000] = { 0, };
	unsigned char Seed[64] = { 0, };

	fp_req = fopen("SHA2(512)Monte.req", "r");
	fp_fax = fopen("SHA2(512)Monte.fax", "w");

	if (fp_req == NULL || fp_fax == NULL)
	{
		printf("���Ͽ��� ����\n");
		return;
	}

	printf("���Ͽ��� ����\n");

	while (fgets(L_buff, sizeof(L_buff), fp_req) != NULL)
	{
		/*****************L******************/
		printf("%s", L_buff);
		fputs(L_buff, fp_fax);
		memset(L_buff, 0, sizeof(L_buff));
		fprintf(fp_fax, "\n");
		/*****************Enter******************/
		fgets(buf, sizeof(buf), fp_req);
		memset(buf, 0, sizeof(buf));
		/****************Seed******************/
		fgets(Seed_buff, sizeof(Seed_buff), fp_req);
		printf("%s", Seed_buff);
		fputs(Seed_buff, fp_fax);
		Ascii(Seed_buff, Seed, &Seed_len);
		memset(Seed_buff, 0, sizeof(Seed_buff));
		/******************Enter********************/
		fgets(buf, sizeof(buf), fp_req);
		memset(buf, 0, sizeof(buf));
	}
	printf("\n");
	fprintf(fp_fax, "\n");

	unsigned char MD[1003][64] = { 0, };
	unsigned char M[1003][192] = { 0, };

	for (j = 0; j < 100; j++)
	{
		printf("COUNT = %d\n", j);
		fprintf(fp_fax, "COUNT = %d\n", j);

		for (n = 0; n < 64; n++)
		{
			MD[0][n] = Seed[n];
			MD[1][n] = Seed[n];
			MD[2][n] = Seed[n];
		}

		for (i = 3; i < 1003; i++)
		{
			for (n = 0; n < 64; n++)
			{
				M[i][n] = MD[i - 3][n];
			}
			for (n = 64; n < 128; n++)
			{
				M[i][n] = MD[i - 2][n - 64];
			}
			for (n = 128; n < 192; n++)
			{
				M[i][n] = MD[i - 1][n - 128];
			}

			SHA512(M[i], 192, MD[i]);
		}

		for (n = 0; n < 64; n++)
		{
			Seed[n] = MD[1002][n];
		}

		printf("MD = ");
		for (n = 0; n < 64; n++)
		{
			printf("%02X", MD[1002][n]);
		}
		printf("\n");
		printf("\n");

		//���Ͽ� ���ֱ�
		fprintf(fp_fax, "MD = ");
		for (n = 0; n < 64; n++)
		{
			fprintf(fp_fax, "%02X", MD[1002][n]);
		}
		fprintf(fp_fax, "\n");
		fprintf(fp_fax, "\n");

	}

	fclose(fp_req);
	fclose(fp_fax);

}
