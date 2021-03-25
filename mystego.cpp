#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define inf 987654321
#define HEADERSIZE 54 // ��� ũ��� 54
#define RGBSIZE 8 // RGB ũ��� 8
char headerInfo[HEADERSIZE]; // ����� ���� �迭
char buffer[inf]; // �̹��� ������ ���� �迭

int main(int argc, char* argv[])
{
	char command = argv[1][0];
	string input = "origin.bmp";
	string output = "stego.bmp";

	switch (command)
	{
		case 'e':
		{
			string content; // �Է¹��� ���ڿ�
			getline(cin, content);
			fstream inp;            // origin.bmp ����
			fstream outp;          // stego.bmp ����
			inp.open(input, ios::in | ios::binary);
			outp.open(output, ios::out | ios::binary | ios::trunc);
			
			inp.seekg(0, ios::end);
			int fileSize = inp.tellg();
			inp.seekg(0, ios::beg);

			inp.read(headerInfo, HEADERSIZE);

			int imageSize = fileSize - HEADERSIZE; // �̹������� ũ��
			inp.read(buffer, imageSize);
			int rgb_idx = 0;
			for (int i = 0; i < content.size(); i++) // content ��Ʈ �߰�
			{
				int cur_char = content[i];
				for (int j = rgb_idx; j < rgb_idx + RGBSIZE; j++)
				{
					int cur_charBit = cur_char % 2;  // ��Ʈ �� �����
					buffer[j] -= (int)buffer[j] % 2; // ��Ʈ�� 0���� ������
					buffer[j] += cur_charBit;  // ��Ʈ �� ���ϱ�
					cur_char /= 2;
				}
				rgb_idx += RGBSIZE;
			}
			int cur_char = '\0'; // ���� ������� �ι��� ����
			for (int i = rgb_idx; i < rgb_idx + RGBSIZE; i++)
			{
				int cur_charBit = cur_char % 2;
				buffer[i] -= (int)buffer[i] % 2;
				buffer[i] += cur_charBit;
				cur_char /= 2;
			}
			outp.write(headerInfo, HEADERSIZE);
			outp.write(buffer, imageSize);
			
			inp.close();
			outp.close();
			break;
		}
		case 'd':
		{
			fstream outp;
			outp.open("stego.bmp", ios::in | ios::binary);

			outp.seekg(0, ios::end);
			int fileSize = outp.tellg();
			outp.seekg(0, ios::beg);
			int imageSize = fileSize - HEADERSIZE;
			outp.read(headerInfo, HEADERSIZE);
			outp.read(buffer, imageSize);

			int rgb_idx = 0;
			for (int i = 0; i < imageSize; i++)
			{
				int cur_charBit = 0;
				for (int j = rgb_idx; j < rgb_idx + RGBSIZE; j++)
				{
					int tmp = (int)buffer[j] % 2;
					int cnt = j - rgb_idx;
					cur_charBit += tmp << cnt;
				}
				if (cur_charBit == (int)'\0')
				{
					return 0;
				}
				cout << (char)cur_charBit;
				rgb_idx += RGBSIZE;
			}
			break;
		}
	}
}