#include "./statMod.h"

StatMod::StatMod() {
        sum_x = 0;
        sum_xx = 0;
        sum_x2 = 0;
        sum_x3 = 0;
        sum_x4 = 0;
        M = 0;

        mu_y = 0;
        sum_y = 0;
        sum_y2 = 0;
        sum_yy = 0;
        sum_y3 = 0;
        sum_y4 = 0;
}

StatMod::~StatMod() {
}


void StatMod::add(std::complex<double> x) {
        sum_x += x;
        double x2 = (x*std::conj(x)).real();
        sum_xx += x*x;
        sum_x2 += x2;
        sum_x3 += x*x2;
        sum_x4 += x2*x2;
        M += 1;
}

void StatMod::addOpt(std::complex<double> x) {
        std::complex<double> y = x - mu_y;
        sum_y += y;
        double y2 = std::real(y*std::conj(y));
        sum_y2 += y2;
        sum_yy += y*y;
        sum_y3 += y2*y;
        sum_y4 += y2*y2;


        this->add(x);

        if (std::abs(sum_y/static_cast<double>(M) - mu_y) > 0.01 || M == 1 || M%4000 == 0) {
                // std ::cout << "r!  " << M << "    " << std::abs(sum_y - sum_y_last) << '\n';
                // mean_varOpt();
                recentering();
        }
}

void StatMod::recentering() {
        std::complex<double> dmu_y =  sum_y / (1.0*M) - mu_y;
        mu_y = mu_y + dmu_y;
        double dmu_y2 = std::real(std::conj(dmu_y)*dmu_y);
        std::complex<double> dmu_y3 = dmu_y2*dmu_y;

        std::complex<double> sum_y_l = sum_y;
        std::complex<double> sum_yy_l = sum_yy;
        double sum_y2_l = sum_y2;
        std::complex<double> sum_y3_l = sum_y3;
        double sum_y4_l = sum_y4;

        sum_y = sum_y_l - dmu_y*static_cast<double>(M);

        sum_y2 = sum_y2_l + M*dmu_y2 - std::real(std::conj(sum_y_l)*dmu_y + std::conj(dmu_y)*sum_y_l);

        sum_y3 = sum_y3_l + 2.0*sum_y_l*dmu_y2 - std::conj(dmu_y)*sum_yy_l - 2.0*dmu_y*sum_y2_l - (1.0*M)*dmu_y3 + dmu_y2*std::conj(sum_y_l);

        sum_y4 = std::real(sum_y4_l + M*dmu_y2*dmu_y2 - 2.0*dmu_y3*std::conj(sum_y_l) + sum_yy_l*std::conj(dmu_y*dmu_y) - 2.0*sum_y3_l*std::conj(dmu_y));
        sum_y4 += -std::real(2.0*sum_y_l*std::conj(dmu_y3) - 2.0*dmu_y*std::conj(sum_y3_l) + 4.0*dmu_y2*sum_y2);
}

void StatMod::mean_var() {
        std::complex<double> mean;
        std::complex<double> variance;
        mean = sum_x / (1.0*M);
        variance = (sum_x2 - std::real(std::conj(mean)*mean)*M) / (M-1.0);
        std::cout << "mean: " << std::abs(mean) << " ,    variance: " << std::abs(variance) << '\n';
}

void StatMod::mean_varOpt() {
        std::complex<double> mean;
        std::complex<double> variance;
        std::complex<double> varianceAlt;

        // recentering();

        mean = (sum_y / static_cast<double>(M)) + mu_y;
        std::complex<double> s_x2 = sum_y2 + (1.0*M)*(std::conj(mu_y)*mu_y) + (std::conj(mu_y)*sum_y) + (std::conj(sum_y)*mu_y);


        variance = std::real(s_x2 - std::conj(mean)*mean*(1.0*M)) / (M-1.0);

        std::cout << "mean: " << std::abs(mean) << " ,    variance: " << std::abs(variance) << '\n';
        // std::cout << "mean: " << std::abs(mean) << " ,    variance: " << std::abs(variance) << "   (Opt)" << '\n';
}

std::complex<double> StatMod::mean() {
        return (sum_x / (1.0*M));
}
std::complex<double> StatMod::meanOpt() {
        return (sum_y / (1.0*M)) + mu_y;
}

double StatMod::var() {
        std::complex<double> mean = this->mean();
        return std::abs(sum_x2 - (std::conj(mean)*mean).real()*M) / (M-1.0);
}
double StatMod::varOpt() {
        std::complex<double> mean = this->meanOpt();
        std::complex<double> s_x2 = sum_y2 + (1.0*M)*(std::conj(mu_y)*mu_y) + (std::conj(mu_y)*sum_y) + (std::conj(sum_y)*mu_y);
        return std::abs(s_x2 - (std::conj(mean)*mean).real()*M) / (M-1.0);
}

void StatMod::var_of_var() {
        std::complex<double> mu = this->mean();
        double var = this->var();
        double var_var;
        double mu2;
        double mu_4;
        mu2 = (mu*std::conj(mu)).real();
        mu_4 = (sum_x4 - 4*(sum_x3*std::conj(mu)).real() + 4.0*(sum_x2*mu2) + 2.0*(sum_xx*std::conj(mu*mu)).real() - 3*mu2*mu2) / (1.0*M);
        var_var = (mu_4 - var*var) / (1.0*M);

        std::cout << " var_var: " << var_var << '\n';
}

void StatMod::var_of_varOpt() {
        double mu_y2 = std::real(mu_y*std::conj(mu_y));
        std::complex<double> s_xx = sum_yy + (1.0*M)*(mu_y2) + 2.0*(mu_y*sum_y);
        double s_x2 = std::real(sum_y2 + (1.0*M)*(mu_y2) + (std::conj(mu_y)*sum_y) + (std::conj(sum_y)*mu_y));
        std::complex<double> s_x3 = sum_y3 + 2.0*sum_y*mu_y2 + 2.0*sum_y2*mu_y + sum_yy*std::conj(mu_y) + sum_y*mu_y2 + (1.0*M)*mu_y*mu_y2;

        // double s_x4 = sum_y4 + mu_y2*mu_y2;
        double s_x4 = std::real(sum_y4 + (1.0*M)*mu_y2*mu_y2 + mu_y2*std::conj(sum_yy) + 2.0*sum_y*mu_y2*mu_y + sum_yy*mu_y2);
        s_x4 += std::real(2.0*sum_y3*std::conj(mu_y) + 2.0*mu_y2*std::conj(mu_y)*sum_y + 4.0*mu_y2*sum_y2 + 2.0*sum_y3*mu_y);


        std::complex<double> mean = this->meanOpt();
        double var = this->varOpt();
        double var_var;
        double mean2;
        double mu_4;

        mean2 = std::real(mean*std::conj(mean));
        mu_4 = (s_x4 - 4*(s_x3*std::conj(mean)).real() + 4.0*(s_x2*mean2) + 2.0*(s_xx*std::conj(mean*mean)).real() - 3.0*mean2*mean2) / (1.0*M);
        var_var = (mu_4 - var*var) / (1.0*M);

        std::cout << " var_var: " << var_var << '\n';
        // std::cout << " var_var: " << var_var << "   (Opt)" << '\n';
}
