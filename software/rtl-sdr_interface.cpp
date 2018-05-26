#include <iostream>
#include <vector>
#include <cstdint>
#include <complex>


#include "global_constants.h"
#include "librtlsdr/include/rtl-sdr.h"
#include "librtlsdr/src/convenience/convenience.h"


#define GAIN 100
#define BLOCK_SIZE 16*16384	//not less than 512


using namespace std;

class T_rtlsdr {
private:

	rtlsdr_dev_t *dev = NULL;

	uint32_t center_freq;

	vector<uint8_t> current_samples;

	void convert_samples() {

		int total = current_samples.size() / 2;
		double tmp_real, tmp_imag;

		last_samples.clear();
		last_samples.reserve(total);

		for(int i = 0; i < total; i++) {

			tmp_real = ((double)current_samples[2*i] - 127) * 0.008;
			tmp_imag = ((double)current_samples[2*i + 1] - 127) * 0.008;

			(last_samples[i]).real( tmp_real );
			(last_samples[i]).imag( tmp_imag );
		}

	}

public:

	vector< complex<double> > last_samples;

	T_rtlsdr() {

	}

	~T_rtlsdr() {

		rtlsdr_close(dev);

	}

	void init() {

		int stat = 0;
		int dev_index = 0;
		int gain = 0;

		dev_index = verbose_device_search("0");
		if(dev_index < 0) {
			cout << "Device not found!" << endl;
			exit(1);
		}

		stat = rtlsdr_open(&dev, (uint32_t)dev_index);
		if (stat < 0) {
			cout << "Failed to open rtlsdr device #" << dev_index << endl;
			exit(1);
		}

		verbose_set_sample_rate(dev, SAMPLE_RATE);

		gain = nearest_gain(dev, GAIN);	//no AGC
		verbose_gain_set(dev, gain);

		cout << "Dongle init done" << endl;

	}

	void set_freq(double freq) {

		center_freq = (uint32_t)freq;
		verbose_set_frequency(dev, (uint32_t)freq);

	}

	double get_freq() {

		return( (double)center_freq );

	}

	void get_samples() {

		int samples_read = 0;
		int totally_read = 0;
		int stat;
		bool reread = false;
		bool done = false;
		void *buf;

		int n = 2 * fft_length;	//need 2n real samples for n complex ones

		current_samples.clear();
		current_samples.reserve(n);
		buf = (void *)current_samples.data();
		while(!done) {
			if(reread) {
				current_samples.clear();
				buf = (void *)current_samples.data();
				totally_read = 0;
			}

			if((n - totally_read) >= BLOCK_SIZE) {

				stat = rtlsdr_read_sync(dev,
							(void*)(buf),
							BLOCK_SIZE,
							&samples_read
							);

				if(stat < 0) {
					cout << "Read failed" << endl;
					reread = 1;
				}
				else if(samples_read < BLOCK_SIZE) {
					cout << "Short read" << endl;
					reread = 1;
				}
				else {
					if(reread == 1)
						reread = 0;
					totally_read += BLOCK_SIZE;
					buf = (void *)((uint8_t *)buf + BLOCK_SIZE);
				}
			}
			else {

				stat = rtlsdr_read_sync(dev,
							(void*)(buf),
							n - totally_read,
							&samples_read
							);
				if(stat < 0) {
					cout << "Read failed" << endl;
					reread = 1;
				}
				else if(samples_read < (n - totally_read)) {
					cout << "Short read" << endl;
					reread = 1;
				}
				else {
					if(reread == 1)
						reread = 0;
					done = true;
				}
			}
		}

	convert_samples();

	}
}
;
