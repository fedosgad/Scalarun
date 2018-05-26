/*
 * Abstraction class to convert samples from T_rtlsdr to frequency
 * spectrum and extract information about amplitudes of signals
 *
 * Constructor:
 * 	TSpectre( const *T_rtlsdr input_obj ) - will use samples from
 * 		"input_obj" object
 *
 * Methods:
 * 	void update() - updates spectre
 * 		Takes new samples from input_obj and performs FFT
 *
 * 	double get_amp( double freq ) - returns amplitude of component
 * 		of frequency freq (absolute value of complex frequency)
 */

class TSpectre {
public:

	TSpectre( const *T_rtlsdr input );

	void update();

	double get_amp( double freq );
}
;
