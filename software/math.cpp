#include <vector>
#include <complex>


#include "global_constants.h"
#include "rtl-sdr_interface.hpp"
#include "fftw++/fftw++.h"


using namespace std;
using namespace fftwpp;


class TSpectre {
private:

	vector< complex<double> > spectre;

	fft1d *Forward;

	T_rtlsdr input;

public:

	TSpectre( const T_rtlsdr& input_obj ) {

		input = input_obj;

		spectre.reserve(fft_length);
		fftw::maxthreads = get_max_threads();
		Forward = new fft1d(fft_length, -1, input.last_samples.data(), spectre.data());

	}

	void update() {

		(*Forward).fft(input.last_samples.data(), spectre.data());

	}

	double get_amp( double freq ) {
		
	}
};
