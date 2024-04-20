#include "rational.h"

Rational::Rational() {
    numer_ = 0;
    denom_ = 1;
}

Rational::Rational(int value) {  // NOLINT
    numer_ = value;
    denom_ = 1;
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    if (numer < 0 && denom < 0) {
        numer = std::abs(numer);
        denom = std::abs(denom);
    } else if (denom < 0 && numer >= 0) {
        numer = -numer;
        denom = std::abs(denom);
    }
    int64_t gcd = std::gcd(std::abs(numer), std::abs(denom));
    if (gcd != 1) {
        numer /= gcd;
        denom /= gcd;
    }
    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero{};
    }
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.denom_ + rhs.numer_ * lhs.denom_, rhs.denom_ * lhs.denom_);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.numer_ * rhs.numer_, rhs.denom_ * lhs.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.numer_ + ratio.denom_);
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.numer_ - ratio.denom_);
    return ratio;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator(),
                    rhs.GetDenominator() * lhs.GetDenominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + -rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetNumerator(), rhs.GetDenominator() * lhs.GetDenominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    return Rational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
}

Rational operator++(Rational& ratio, int) {
    Rational copy = ratio;
    ++ratio;
    return copy;
}

Rational operator--(Rational& ratio, int) {
    Rational copy = ratio;
    --ratio;
    return copy;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() > rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() <= rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() >= rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() == rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() != rhs.GetNumerator() * lhs.GetDenominator();
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int numer = 0;
    int denom = 0;
    std::string input;
    is >> input;
    if (input.find("/") != std::string::npos) {
        numer = std::stoi(input.substr(0, input.find("/")));
        denom = std::stoi(input.substr(input.find("/") + 1, input.size()));
    } else {
        numer = std::stoi(input);
        denom = 1;
    }
    ratio.Set(numer, denom);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
    }
    return os;
}