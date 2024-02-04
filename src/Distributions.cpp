#include "Distributions.h"


const double PI = 3.141592653589793;



__declspec(dllexport) double WINAPI ND(double x) // normal distribution
{
	return exp(-pow(x, 2) / 2) / sqrt(2 * PI);
}


__declspec(dllexport) double WINAPI CND(double x) // cumulative normal distribution
{
	double y = abs(x);
	double threshold_return0 = 37;

	if (y > threshold_return0)
	{
		if (x > 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		double gauss_y = exp(-pow(y, 2) / 2);
		double threshold_approx = 7.07106781186547;
		double SumA, SumB, out;

		if (y < threshold_approx)
		{
			SumA = 0.0352624965998911 * y + 0.700383064443688;
			SumA = SumA * y + 6.37396220353165;
			SumA = SumA * y + 33.912866078383;
			SumA = SumA * y + 112.079291497871;
			SumA = SumA * y + 221.213596169931;
			SumA = SumA * y + 220.206867912376;
			SumB = 0.0883883476483184 * y + 1.75566716318264;
			SumB = SumB * y + 16.064177579207;
			SumB = SumB * y + 86.7807322029461;
			SumB = SumB * y + 296.564248779674;
			SumB = SumB * y + 637.333633378831;
			SumB = SumB * y + 793.826512519948;
			SumB = SumB * y + 440.413735824752;
			out = gauss_y * SumA / SumB;
		}
		else
		{
			SumA = y + 0.65;
			SumA = y + 4 / SumA;
			SumA = y + 3 / SumA;
			SumA = y + 2 / SumA;
			SumA = y + 1 / SumA;
			out = gauss_y / (SumA * 2.506628274631);
		}
		
		if (x > 0)
		{
			out = 1 - out;
		}
		return out;
	}
}


__declspec(dllexport) double WINAPI CBND(double x, double y, double rho) // cumulative bivariate normal distribution
{
	int MaxNG = 3;
	int MaxLG = 10;
	double** W = new double* [MaxLG];
	double** XX = new double* [MaxLG];
	for (int i = 0; i < MaxLG; ++i) {
		W[i] = new double[MaxNG];
		XX[i] = new double[MaxNG];
	}

	W[0][0] = 0.17132449237917;
	XX[0][0] = -0.932469514203152;
	W[1][0] = 0.360761573048138;
	XX[1][0] = -0.661209386466265;
	W[2][0] = 0.46791393457269;
	XX[2][0] = -0.238619186083197;
	W[0][1] = 4.71753363865118E-02;
	XX[0][1] = -0.981560634246719;
	W[1][1] = 0.106939325995318;
	XX[1][1] = -0.904117256370475;
	W[2][1] = 0.160078328543346;
	XX[2][1] = -0.769902674194305;
	W[3][1] = 0.203167426723066;
	XX[3][1] = -0.587317954286617;
	W[4][1] = 0.233492536538355;
	XX[4][1] = -0.36783149899818;
	W[5][1] = 0.249147045813403;
	XX[5][1] = -0.125233408511469;
	W[0][2] = 1.76140071391521E-02;
	XX[0][2] = -0.993128599185095;
	W[1][2] = 4.06014298003869E-02;
	XX[1][2] = -0.963971927277914;
	W[2][2] = 6.26720483341091E-02;
	XX[2][2] = -0.912234428251326;
	W[3][2] = 8.32767415767048E-02;
	XX[3][2] = -0.839116971822219;
	W[4][2] = 0.10193011981724;
	XX[4][2] = -0.746331906460151;
	W[5][2] = 0.118194531961518;
	XX[5][2] = -0.636053680726515;
	W[6][2] = 0.131688638449177;
	XX[6][2] = -0.510867001950827;
	W[7][2] = 0.142096109318382;
	XX[7][2] = -0.37370608871542;
	W[8][2] = 0.149172986472604;
	XX[8][2] = -0.227785851141645;
	W[9][2] = 0.152753387130726;
	XX[9][2] = -7.65265211334973E-02;

	int NG, LG;
	if (abs(rho) < 0.3)
	{
		NG = 0;
		LG = 2;
	}
	else if (abs(rho) < 0.75)
	{
		NG = 1;
		LG = 5;
	}
	else
	{
		NG = 2;
		LG = 9;
	}

	double h = -x;
	double k = -y;
	double hk = h * k;
	double BVN = 0;

	if (abs(rho) < 0.925)
	{
		if (abs(rho) > 0)
		{
			double hs = (h * h + k * k) / 2.;
			double asr = asin(rho);
			for (int i = 0; i <= LG; i++)
			{
				for (int ISs = -1; ISs <= 1; ISs +=2)
				{
					double sn = sin(asr * (ISs * XX[i][NG] + 1) / 2.);
					double tmp = W[i][NG];
					BVN += W[i][NG] * exp((sn * hk - hs) / (1 - sn * sn));
				}
			}
			BVN *= asr / (4. * PI);

		}
		BVN += CND(-h) * CND(-k);
	}
	else
	{
		if (rho < 0)
		{
			k = -k;
			hk = -hk;
		}
		if (abs(rho) < 1)
		{
			double Ass = (1 - rho) * (1 + rho);
			double a = sqrt(Ass);
			double bs = pow(h - k, 2);
			double c = (4 - hk) / 8.;
			double d = (12 - hk) / 16.;
			double asr = -(bs / Ass + hk) / 2.;
			if (asr > -100)
			{
				BVN = a * exp(asr) * (1 - c * (bs - Ass) * (1 - d * bs / 5.) / 3. + c * d * Ass * Ass / 5.);
			}
			if (-hk < 100)
			{
				double b = sqrt(bs);
				BVN -= exp(-hk / 2) * sqrt(2 * PI) * CND(-b / a) * b * (1 - c * bs * (1 - d * bs / 5.) / 3.);
			}
			a /= 2.;
			for (int i = 0; i <= LG; i++)
			{
				for (int ISs = -1; ISs <= 1; ISs += 2)
				{
					double xs = pow(a * (ISs * XX[i][NG] + 1), 2);
					double rs = sqrt(1 - xs);
					double asr = -(bs / xs + hk) / 2;
					if (asr > -100)
					{
						BVN += W[i][NG] * exp(asr) * (exp(-hk * (1 - rs) / (2 * (1 + rs))) / rs - (1 + c * xs * (1 + d * xs)));
					}
				}
			}
			BVN /= -(2 * PI);

		}
		if (rho > 0)
		{
			BVN += CND(-max(h, k));
		}
		else
		{
			BVN *= -1;
			if (k > h)
			{
				BVN += CND(k) - CND(h);
			}
		}
	}
	double out = BVN;
	return out;
}





double __stdcall PoissonDistribution(double x, long k)
{
	double out = 1;
	for (long i = 1; i <= k; i++) // Œ…—Ž‚¿‰ñ”ð‚Ì‚½‚ßA‰ðÍŽ®‚Å‚Í‚È‚­for•¶‚ð‰ñ‚·
	{
		out *= x / i;
	}
	out *= exp(-x);
	return out;
}


double RationalApproximation(double t)
{
	// Abramowitz and Stegun formula 26.2.23.
	// The absolute value of the error should be less than 4.5 e-4.
	double c[] = { 2.515517, 0.802853, 0.010328 };
	double d[] = { 1.432788, 0.189269, 0.001308 };
	return t - ((c[2] * t + c[1]) * t + c[0]) /
		(((d[2] * t + d[1]) * t + d[0]) * t + 1.0);
}


double NormalCDFInverse(double p)
{
	if (p <= 0.0 || p >= 1.0)
	{
		return 0;
	}

	// See article above for explanation of this section.
	if (p < 0.5)
	{
		// F^-1(p) = - G^-1(p)
		return -RationalApproximation(sqrt(-2.0 * log(p)));
	}
	else
	{
		// F^-1(p) = G^-1(1-p)
		return RationalApproximation(sqrt(-2.0 * log(1 - p)));
	}
}





