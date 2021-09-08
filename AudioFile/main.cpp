#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

union chr4toint {
	int int_val;
	char char_val[4];
};
class waveHeader {
	public:
		waveHeader() {};
		int chunkID, chunkSize, Format, subChunkID, subChunk1size;
		short audioFormat, numChannels;
		int sampleRate, byteRate;
		short blockAlign, bitsPerSample;
		int subChunk2ID, subChunk2size;

		bool WriteWaveHeader(int Amp, int freq, int len, int bytr, int channels)
		{
			chr4toint chnk;
			chnk.char_val[0] = 'R';
			chnk.char_val[1] = 'I';
			chnk.char_val[2] = 'F';
			chnk.char_val[3] = 'F';
			this->chunkID = chnk.int_val;

			this->chunkSize = bytr * len * channels + 36;

			chnk.char_val[0] = 'W';
			chnk.char_val[1] = 'A';
			chnk.char_val[2] = 'V';
			chnk.char_val[3] = 'E';
			this->Format = chnk.int_val;

			chnk.char_val[0] = 'f';
			chnk.char_val[1] = 'm';
			chnk.char_val[2] = 't';
			chnk.char_val[3] = ' ';
			this->subChunkID = chnk.int_val;

			this->subChunk1size = 16;
			this->audioFormat = 1;
			this->numChannels = channels;
			this->sampleRate = freq;
			this->byteRate = freq * bytr * channels;
			this->blockAlign = bytr * channels;
			this->bitsPerSample = bytr * 8;

			chnk.char_val[0] = 'd';
			chnk.char_val[1] = 'a';
			chnk.char_val[2] = 't';
			chnk.char_val[3] = 'a';
			this->subChunk2ID = chnk.int_val;
			this->subChunk2size = freq * channels * bytr * len;

			return true;
		}
};

int main(int argc, char* argv[])
{
	waveHeader wav;

	//Sprint 1

	double PI = 3.141592;

	short* dat;
	dat = new short[44100];
	for (int i = 0; i < 44100; i++)
	{
		dat[i] = sin(2 * PI * 440. * (double)i / 44100.) * 10000;
	}

	//Sprint 2

	ofstream mywave("mydata.wav", ios::binary | ios::out);
	mywave.write((char*)dat, sizeof(short) * 44100 * 1);
	mywave.close();

	//Sprint 3

	int f = 440, A = 10000, fs = 44100, len = 1; // in sec
	int bytr = sizeof(short) , channels = 1;

	wav.WriteWaveHeader(A, fs, len, bytr, channels);

	waveHeader wav2;

	ifstream beatles("Beatles.wav", ios::binary | ios::out);
	beatles.read((char*)&wav2, sizeof(waveHeader));

	cout << wav2.numChannels << endl;

	//Sprint 4

	mywave.open("mywave.wav", ios::binary | ios::out);
	mywave.write((char*)&wav, sizeof(waveHeader));
	mywave.write((char*)dat, ((int) sizeof(short)) * fs * channels);
	mywave.close();

	delete[] dat;

	// Plus Alpha
	A = 10000, fs = 44100, len = 10; // in sec
	bytr = sizeof(short), channels = 1;
	dat = new short[fs * len];

	for (int i = 0; i < fs * len; i++)
	{
		dat[i] = 0;
	}

	for (int i = 0; i < fs * len; i++)
	{
		double t = (double)i / (double)fs;
		dat[i] += sin(2 * PI * (65.4075 * t + ((261.630 - 65.4075) / 10. * t * t))) * 1000. / (1. + t / 8.);
		dat[i] += sin(2 * PI * (130.815 * t + ((523.260 - 130.815) / 10. * t * t))) * 1000. / (1. + t / 8.);
		dat[i] += sin(2 * PI * (261.630 * t + ((1046.52 - 261.630) / 10. * t * t))) * 1000. / (1. + t / 8.);
		dat[i] += sin(2 * PI * (523.260 * t + ((2093.04 - 523.260) / 10. * t * t))) * 1000. / (1. + t / 8.);
		dat[i] += sin(2 * PI * (1046.52 * t + ((4186.08 - 1046.52) / 10. * t * t))) * 1000. / (1. + t / 8.);
		dat[i] += sin(2 * PI * (2093.04 * t + ((8372.16 - 2093.04) / 10. * t * t))) * 1000. / (1. + t / 8.);
	} 

	wav.WriteWaveHeader(A, fs, len, bytr, channels);

	mywave.open("myunique.wav", ios::binary | ios::out);
	mywave.write((char*)&wav, sizeof(waveHeader));
	mywave.write((char*)dat, ((int)sizeof(short)) * fs * channels * len);
	mywave.close();

	delete[] dat;
}