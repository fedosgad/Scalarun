/*
 * Interface class for RTL-SDR dongles.
 * Variables:
 * 	std::vector< complex<double> > last_samples - samples from the
 * 	last get_samples(n) call. Shrunk to the exact size (n).
 * 
 * Methods:
 * 	void init() - finds and configures dongle
 * 
 * 	void set_freq(int freq) - tune dongle to central frequency
 * 		Maybe will have offset from the actual frequency passed
 * 		to avoid distortion by DC spike
 * 		freq is actually uint32_t
 *
 * 	void get_samples(int n) - get n samples from the dongle
 * 		Samples are stored in internal vector last_samples
 */

class T_rtlsdr {
private:

public:

	std::vector< complex<double> > last_samples;

	void init();

	void set_freq(int freq);

	void get_samples(int n);
}
;
