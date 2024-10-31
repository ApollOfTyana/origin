#include <iomanip>
#include <iostream>
#include <fstream>

using  namespace std;

class Address {

  public:
  ifstream fO;
  ofstream fU;
  string city , street;
  int street_number, house_number;

  Address** create_massive()
  {
    return create_addressesFromFile();
  };

  void write_massiveIndex_inOutFile(Address** adress, int ID) {
    fU << *&adress[ID]->city << ", " << *&adress[ID]->street << ", " << *&adress[ID]->street_number << ", " << *&adress[ID]->house_number << "\n";
  };

  void sort_city_name(Address** addresses, int size) {
    for (int i = 0; i < size - 1; ++i) {
      for (int j = 0; j < size - i - 1; ++j) {
          if (addresses[j]->city > addresses[j + 1]->city) {
              swap(addresses[j], addresses[j + 1]);
          }
      }
    }
  }

  void show_adress() const {
    cout << city << ", " << street << ", " << street_number << ", " << house_number << endl;
  };

  Address(string in_city, string in_street, int in_street_number, int in_house_number) : city(in_city), street(in_street), street_number(in_street_number), house_number(in_house_number) {}
  Address(string file_in, string file_out){
    
    fO.open(file_in);
    fU.clear();
    fU.open(file_out);
  };

  private:

    Address** create_addressesFromFile()
    {
      string size;
      int schet_writed_address=0;
      
      fO>>size;

      Address** addresses = new Address*[static_cast<size_t>(atoi(size.c_str()))];

      while(schet_writed_address<atoi(size.c_str()))
      {
        fO >> city >> street >> street_number >> house_number;
        addresses[schet_writed_address] = new Address( city, street, street_number, house_number);
        schet_writed_address++;
      }
      fO.close();

      return addresses;
    }

};

int main(int argc, char** argv){
    
    Address a("in.txt","outs.txt");
    //cout << a.get_address();
    Address** aa = a.create_massive();

    a.write_massiveIndex_inOutFile(aa,0);
    a.write_massiveIndex_inOutFile(aa,1);
    a.write_massiveIndex_inOutFile(aa,2);
    a.write_massiveIndex_inOutFile(aa,3);
    a.write_massiveIndex_inOutFile(aa,4);
    
    a.sort_city_name(aa,5);

    a.write_massiveIndex_inOutFile(aa,0);
    a.write_massiveIndex_inOutFile(aa,1);
    a.write_massiveIndex_inOutFile(aa,2);
    a.write_massiveIndex_inOutFile(aa,3);
    a.write_massiveIndex_inOutFile(aa,4);


    return 0;
}

