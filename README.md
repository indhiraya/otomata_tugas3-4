  | Nama                      | NRP        |
  |:-------------------------:|:----------:|
  | Almira Fidela Soehartanto Putri | 5025221222 |
  | Adelia Putri Kamaski        | 5025221320 |
  | Indhira Ayu Puspita Ningrum | 5025231316 |
  | Imelda Alexis Jovita  | 5025231032 |
  
  # Otomata - E (Ilham Gurat Adillion) Tugas 3

  ## Penjelasan Algoritma
  1. Masukkan start_state ke dalam path.
  2. cek test_string per index.
  3. Pilih state yang sesuai dengan current_state, lalu pilih alphabet yang sesuai dengan test_string yang sedang di akses. jika ada perbarui current_state dan path. jika tidak ada maka outputkan:
```
path: xxx
Status: REJECTED
```
  4. Ulangi step ke 3 hingga test_string mencapai \0 dan outputkan path dan Status: ACCEPTED apabila path paling kanan/bawah == accepted state dan Status: Rejected apabila path paling kanan/bawah != accepted state.
    ```
    Path: xxx -> xxx ...
    Status: ACCEPTED/REJECTED
    ```
  ## Penjelasan Source Code
  1. gunakan header `<nlohmann/json.hpp>` untuk library JSON dan `<fstream>` untuk membaca file JSON
  2. `ifstream file("tes.json");` untuk membaca file JSON
  4. simpan data json pada variabel `data` lalu pilah data dengan memasukkan masing-masing data pada variabel yang berbeda sebagai berikut:
```
vector<string> states = data["states"].get<vector<string>>();
vector<string> alphabet = data["alphabet"].get<vector<string>>();
string start_state = data["start_state"];
vector<string> accept_states = data["accept_states"].get<vector<string>>();
map<string, map<string, string>> transitions;
for (auto& [state, trans] : data["transitions"].items()) {
  for (auto& [input, next_state] : trans.items()) {
    transitions[state][input] = next_state;
  }
}
string test_string = data["test_string"];
```
  5. Buat variabel Vector Path untuk menyimpan hasil Path `vector<string> Path;`
  6.  inisialisasi `current_state` untuk menyimpan next state
  7.  cek test_string per index
  8.  cari transisi yang sesuai dengan current_state dan test_string yang di akses untuk menghasilkan next path
```
if (transitions[current_state].find(input_str) != transitions[current_state].end()) {
  current_state = transitions[current_state][input_str];
  Path.push_back(current_state);
}
```
  9. Apabila tidak ada current_state atau inputan string yang sesuai maka outputkan path dan status
```
else {
  cout << "Path: ";
  for (int i = 0; i < Path.size(); i++) {
    cout << Path[i];
    if (i < Path.size() - 1) cout << " -> ";
  }

  cout << endl;

  bool result = (find(accept_states.begin(), accept_states.end(), current_state) !=       accept_states.end());
  cout << "Status: " << (result ? "ACCEPTED" : "REJECTED") << endl;
  return 1;
}
```
  10. Jika transition sesuai hingga string terakhir maka outputkan path dan statusnya
```
cout << "Path: ";
for (int i = 0; i < Path.size(); i++) {
  cout << Path[i];
  if (i < Path.size() - 1) cout << " -> ";
}
cout << endl;

bool result = (find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end());
cout << "Status: " << (result ? "ACCEPTED" : "REJECTED") << endl;
```
## Cara Compile dan Run
```
g++ -std=c++17 DFA.cpp -o output
./output
```
      
