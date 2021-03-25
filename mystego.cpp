#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define inf 987654321
#define HEADERSIZE 54 // 헤더 크기는 54
#define RGBSIZE 8 // RGB 크기는 8
char headerInfo[HEADERSIZE]; // 헤더를 담을 배열
char buffer[inf]; // 이미지 내용을 담을 배열

int main(int argc, char* argv[])
{
	char command = argv[1][0];
	string input = "origin.bmp";
	string output = "stego.bmp";

	switch (command)
	{
		case 'e':
		{
			string content; // 입력받을 문자열
			getline(cin, content);
			fstream inp;            // origin.bmp 열기
			fstream outp;          // stego.bmp 열기
			inp.open(input, ios::in | ios::binary);
			outp.open(output, ios::out | ios::binary | ios::trunc);
			
			inp.seekg(0, ios::end);
			int fileSize = inp.tellg();
			inp.seekg(0, ios::beg);

			inp.read(headerInfo, HEADERSIZE);

			int imageSize = fileSize - HEADERSIZE; // 이미지내용 크기
			inp.read(buffer, imageSize);
			int rgb_idx = 0;
			for (int i = 0; i < content.size(); i++) // content 비트 추가
			{
				int cur_char = content[i];
				for (int j = rgb_idx; j < rgb_idx + RGBSIZE; j++)
				{
					int cur_charBit = cur_char % 2;  // 비트 값 만들기
					buffer[j] -= (int)buffer[j] % 2; // 비트를 0으로 돌리고
					buffer[j] += cur_charBit;  // 비트 값 더하기
					cur_char /= 2;
				}
				rgb_idx += RGBSIZE;
			}
			int cur_char = '\0'; // 같은 방법으로 널문자 대입
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