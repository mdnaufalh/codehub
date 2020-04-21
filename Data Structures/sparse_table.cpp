/*
 * NOTES:
 * n <= 3 * 10^7(if more, increase 25 to 26 or 27)
 */
template<typename T> struct rmq {
  vector<vector<T>> sparse_table;
  vector<int> my_log;
  rmq(const vector<T>& arr) {
    	int n = int(arr.size());
      my_log.resize(n + 1);
      sparse_table.resize(n); for(auto& i: sparse_table) i.resize(26);
      my_log[1] = 0;
      for(int i = 0; i < n; ++i) 
        sparse_table[i][0] = arr[i];
      for(int j = 1; j <= 25; ++j) {
        for(int i = 0; i + (1 << j) <= n; ++i) {
          sparse_table[i][j] = min(sparse_table[i][j-1], sparse_table[i + (1 << (j - 1))][j-1]);
        }
      }
      for(int i = 2; i <= n; ++i)
        my_log[i] = my_log[i / 2] + 1;
  }

  T query(int l, int r) {
	  int j = my_log[r - l + 1];
	  return min(sparse_table[l][j], sparse_table[r - (1 << j) + 1][j]);
  }
};
