#include "Dataset.hpp"
#include "NestSet.hpp"

class NestSet;

#define GEN_MAX		1000
#define SET_SIZE	100
#define ABA_RATE	0.1
#define ALPHA		0.1
#define BETA		1.5
#define PI			3.141592
#define COEF_MIN	-1
#define COEF_MAX	1

#define RAND_01	((double)rand() / RAND_MAX)

#define RAND_N	(sqrt(-2.0 * log(RAND_01) * cos(2*PI*RAND_01)))

#define NUME	(tgamma(1*BETA) * sin(PI*BETA/2))
#define DENOM	(tgamma((1+BETA)/2)*BETA*pow(2.0,(BETA-1)/2))
#define SIGMA	pow(NUME / DENOM,1/BETA)

class Nest
{
public:
	Nest(NestSet *argNS);
	~Nest();
	
	void replace(Nest *base);
	void abandon();

	NestSet *ns;
	double *egg;
	double value;
private:
	double evaluate(double *argEgg);
	double *newEgg;
};