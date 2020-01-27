struct IncompatibleDimensionsException : public exception {};
struct IndexOutOfBoundsException : public exception {};
template <typename T> struct Matrix {
	vector<vector<T>> _mat;
    T MOD;
    Matrix(const vector<vector<T>>& mat, T mod = numeric_limits<T>::max()) {
        _mat = mat;
        MOD = mod;
    } 

    Matrix(const Matrix& other, T mod = numeric_limits<T>::max()) {
        _mat = other._mat;
        MOD = mod;
    }

    Matrix(const int n,const int m, T mod = numeric_limits<T>::max()) {
        _mat = vector<vector<T>>(n, vector<T>(m, 0));
        MOD = mod;
    }

    Matrix<T> operator+(Matrix<T>& other) {
        Matrix<T> res(*this, this->MOD);
        if(res.row_count() != other.row_count() || res.col_count() != other.col_count()) {
            throw new IncompatibleDimensionsException();
        }
        for(int i = 0; i < res.row_count(); ++i) {
            for(int j = 0; j < res.col_count(); ++j) {
                res[i][j] += other[i][j];
                res[i][j] %= MOD;
            } 
        }
        return res;
    }

    Matrix<T> operator+(const vector<vector<T>>& other) {
        return (Matrix<T>(other, this->MOD) += *this);
    }

    Matrix<T>& operator+=(const Matrix<T>& other) {
        if(this->col_count() != other.col_count() || this->row_count() != other.row_count()) {
            throw new IncompatibleDimensionsException();
        }
        for(int i = 0; i < this->row_count(); ++i) {
            for(int j = 0; j < this->col_count(); ++j) {
                (*this)[i][j] += other[i][j];
                (*this)[i][j] %= MOD;
            }
        }
        return *this;
    }

    vector<T>& operator[](int i)  {
        if(i >= this->row_count()) {
            throw new IndexOutOfBoundsException();
        }
        return _mat[i];
    }

    Matrix<T>& operator+=(const vector<vector<T>>& other) {
        return (*this += Matrix<T>(other, this->MOD));
    }

    Matrix<T> operator*(Matrix<T>& other) {
        if(this->col_count() != other.row_count()) throw new IncompatibleDimensionsException();
        Matrix<T> ans(this->row_count(), other.col_count(), this->MOD);
        for(int i = 0; i < ans.row_count(); ++i) {
            for(int j = 0; j < ans.col_count(); ++j) {
                ans[i][j] = 0;
                for(int k = 0; k < ans.row_count(); ++k) {
                    ans[i][j] += (*this)[i][k] * other[k][j];
                    ans[i][j] %= MOD;
                }
            }
        }
        return ans;
    }

    Matrix<T> operator*= (Matrix<T>& other) {
         if(this->col_count() != other.row_count()) throw new IncompatibleDimensionsException();
         *this = (*this) * other;
         return (*this);
    }

    Matrix<T> operator^(long long n) {
        Matrix<T> l = (*this);
        Matrix<T> ans(this->row_count(), this->col_count(), this->MOD);
        for(int i = 0; i < min(row_count(), col_count()); ++i) 
            ans[i][i] = 1;
        while(n > 0) {
            if(n % 2 == 1) ans *= l;
            n /= 2;
            l *= l;
        }
        return ans;
    }
    int row_count() const {return _mat.size();}
    int col_count() const {return _mat[0].size();}
	
};

template <typename T> ostream & operator << (ostream &out,const Matrix<T>& mat) {
    for(int i = 0; i < mat._mat.size(); ++i) {
        for(int j = 0; j < mat._mat.size(); ++j) {
            out << mat._mat[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
