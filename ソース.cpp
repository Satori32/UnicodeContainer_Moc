#include <iostream>
#include <vector>
#include <cstring>
#include <string>

struct UTF8_Char
{
	bool Set(char a, char b, char c) {
		A = a;
		B = b;
		C = c;
		return true;
	}
	bool Clear() {
		A = 0;
		B = 0;
		C = 0;
		null = 0;
		return true;
	}
	union {
		struct
		{
			char A;
			char B;
			char C;
			char null;

		};
		char CHAR[4] = { 0, };
	};

};

struct  UTF_8{
	std::vector<UTF8_Char> UTF8;
};

bool Push(UTF_8& In ,UTF8_Char& U) {
	In.UTF8.push_back(U);
	return true;
}

std::vector<UTF8_Char>& GetVector(UTF_8& In) {
	return In.UTF8;
}

bool From(UTF_8& U, const char* S, size_t L) {
	U.UTF8.clear();
	UTF8_Char UC;
	
	char A = 0;
	char B = 0;
	char C = 0;

	for (size_t i = 0; i < L; i++){
		UC.Clear();
		A = S[i++];
		B = S[i];
		if ((B & (1 << 7)) ==0){
			i++;
			C=S[i];
		}
		UC.Set(A,B,C);
		A=0;
		B=0;
		C=0;
		Push(U,UC);
	}
	return true;
}

std::string MakeSingle(UTF_8& U){
	std::string S;

	for (auto& o:GetVector(U)) {
		S += o.CHAR;

	}

	return S;
}

int main() {
	UTF_8 U;
	const char* T = "ˆŸ‚˜I";

	From(U, T, std::strlen(T));

	for (auto& o : GetVector(U)) {
		std::cout << o.CHAR << std::endl;
	}

	std::cout << MakeSingle(U) << std::endl;

	return 0;
}