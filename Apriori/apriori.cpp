#include "stdafx.h"
#include "ADOconn.h"

//int main()
//{
//	CADOConn cadoconn;
//	cadoconn.OnInitADOConn();
//	_RecordsetPtr m_pRecordset;
//	_bstr_t update = "update apriori set count=count+1 where num=%d;";
//	_bstr_t insert = "insert into apriori(num,count) values(%d,%d);";
//	_bstr_t search = "select * from apriori where num=%d;";
//	int a[100];
//	int flag[17000] = { 0 };
//	ifstream in("D:\\retail.dat");
//	if (!in.is_open())
//	{
//		cout << "not open";
//		exit(0);
//	}
//	int k = 0;
//	string p;
//	while (getline(in, p))
//	{
//		//cout << p << endl;
//		istringstream iss(p);
//		int i = 0;
//		while (iss >> a[i])
//		{
//			if (i == 99){
//				cout << a[0] << a[1] << a[2];
//				getchar();
//				getchar();
//			}
//			/*char Search[100];
//			sprintf(Search, search, a[i]);
//			m_pRecordset = cadoconn.GetRecordSet(Search);*/
//			//if ((string)(_bstr_t)m_pRecordset->GetCollect("count") == ""){
//			//if (m_pRecordset->adoEOF)
//			if (flag[a[i]] == 0)
//			{
//				//char Insert[100];
//				/*sprintf(Insert, insert, a[i]);
//				cadoconn.ExecuteSQL(Insert);*/
//				flag[a[i]] = 1;
//			}
//			else
//			{
//				//char Update[100];
//				//sprintf(Update, update, a[i]);
//				//cadoconn.ExecuteSQL(Update);
//				flag[a[i]]++;
//			}
//		}
//	}
//    for (int i = 0; i < 17000; i++)
//	{
//		if (flag[i] >9 ){
//			char Insert[100];
//			sprintf(Insert, insert, i, flag[i]);
//			cadoconn.ExecuteSQL(Insert);
//			cout << i << ":" << flag[i] << endl;
//		}
//	}
//	//int s[14000][14000];
//}
class apriori
{
public:
	map <int, vector<int>> item;
	int min=10;
	map <string, int> CreatItem(int k, map <string , int> L)
	{

	}
	
	map<string, int> first()
	{
		map<string, int> L;
		map<int, vector<int>>::iterator it;
		for (it = item.begin(); it != item.end(); it++){
			vector<int>::iterator it_value;
			for (it_value = it->second.begin(); it_value != it->second.end(); it_value++)
			{
				ostringstream ss;
				string s;
				ss << *it_value;
				s=ss.str();
				L[s] ++;
			}
		}
		map<string, int>::iterator it_L;
		for (it_L = L.begin(); it_L != L.end();)
		{
			if (it_L->second <= min){
				L.erase(it_L++);
			}
			else{
				it_L++;
				cout << it_L->first<<endl;
			}
		}
		return L;
	}
	void FileReader(string URL){
		ifstream in("D:\\retail.dat");
		int k = 0;
		if (!in.is_open())
		{
			cout << "not open";
			exit(0);
		}
		string preline;
		while (getline(in, preline))
		{
			istringstream iss(preline);
			int preitem;
			while (iss >> preitem)
			{
				item[k].push_back(preitem);
			}
			k++;
		}
	}
};
void main(){
	apriori a;
	a.FileReader("D:\\retail.dat");
	cout << "finish";
	map <string, int > L = a.first();
	map <string,int >::iterator it;
	for (it = L.begin(); it != L.end(); it++){
		cout << "key:" << it->first<<" ";
		cout << it->second << endl;
	}
}
