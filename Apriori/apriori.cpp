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
	int min = 1500; int min_2=100;
	map<string, int> firstitem;
	map <string, int> CreatItem(int k, map <string , int> L)
	{
		map<int, vector<int>> preitemset;
		map<string, int> itemset;
		int count = 0;
		map<string, int>::iterator it;
		for (it = L.begin(); it != L.end(); it++)
		{
			vector<int> preline;
			stringstream iss(it->first);
			int preitem;
			while (iss >> preitem){
				preline.push_back(preitem);
			}
			preitemset[count++] = preline;
		}

		int complex[100];
		for (int i = 0; i < count; i++){
			for (int j = i+1; j < count; j++){
				memset(complex,-1,100);
				for (int ii = 0; ii < k - 1; ii++){
					complex[ii] = preitemset[i][ii];
				}
				int kplus = k-1;
				for (int jj = 0; jj < k - 1; jj++){
					bool flag = 1;
					for (int iii = 0; iii < k - 1; iii++){
						if (complex[iii] == preitemset[j][jj]){
							flag = 0;
							break;
						}
					}
					if (flag){
						complex[kplus++] = preitemset[j][jj];
					}
					if (kplus == k + 1){
						break;
					}
				}

				if (kplus == k){
					for (int sortcomi = 0; sortcomi < k; sortcomi++){
						for (int sortcomj = sortcomi; sortcomj < k; sortcomj++){
							if (complex[sortcomi]>complex[sortcomj]){
								int swap = complex[sortcomi];
								complex[sortcomi] = complex[sortcomj];
								complex[sortcomj] = swap;
							}
						}
					}
					int test[100],add=0;
					bool testflag = 0;
					for (int ii = 0; ii < k; ii++){
						for (int jj = 0; jj < k; jj++){
							if (ii == jj){
								continue;
							}
							else{
								test[add++] = complex[jj];
							}
						}
						for (int sorti = 0; sorti < k-1; sorti++){
							for (int sortj = sorti; sortj < k-1; sortj++){
								if (test[sorti]>test[sortj]){
									int swap = test[sorti];
									test[sorti] = test[sortj];
									test[sortj] = swap;
								}
							}
						}

						string strs;
						for (int buildstringi = 0; buildstringi < k-1; buildstringi++){
							stringstream ss;
							ss << test[buildstringi];
							strs += ss.str()+" ";
						}

						map<string, int>::iterator L_test = L.find(strs);
						if (L_test == L.end()){
							testflag = 0;
							break;
						}
						else{
							testflag = 1;
						}
					}
					string itemstrs;
					if (testflag){
						for (int itemi = 0; itemi < k; itemi++){
							stringstream ss;
							ss << complex[itemi];
							itemstrs += ss.str() + " ";
						}
						cout << itemstrs << endl;
						itemset[itemstrs] = 0;
					}
				}
			}
		}
		getchar();
		/*map<string, int >::iterator dsa;
		for (dsa = itemset.begin(); dsa != itemset.end(); dsa++)
		{
			cout << "first" << dsa->first << "  " << dsa->second << endl;
		}*/

		map<int, vector<int>>::iterator it_item;
		for (it_item = item.begin(); it_item != item.end(); it_item++){
			int itemarray[100], creatarray[100], i = 0;
			vector<int>::iterator it_vec;
			for (it_vec = it_item->second.begin(); it_vec != it_item->second.end(); it_vec++){
				itemarray[i++] = *it_vec;
			}
			if (i < k){
				continue;
			}
			else{
				full(itemarray, creatarray, i, k, k, &itemset);
				cout << it_item->first << endl;
			}
		}
		map<string, int>::iterator it_cut;
		for (it_cut = itemset.begin(); it_cut != itemset.end();){
			if (it_cut->second < min_2){
				itemset.erase(it_cut++);
			}
			else{
				it_cut++;
			}
		}
		return itemset;
	}
	
	void full(int a[], int b[], int n, int m, int M, map<string, int> *p_itemset){
		for (int i = n - 1; i >= m - 1; i--){
			b[m - 1] = a[i];
			map<string, int>::iterator it_firstitem;
			stringstream ss;
			ss << a[i];
			string s = ss.str() + " ";
			it_firstitem = firstitem.find(s);
			if (it_firstitem == firstitem.end()){
				continue;
			}
			else{
				if (m > 1){
						full(a, b, i, m - 1, M, p_itemset);
				}
				else{
					string strb;
					for (int j = 0; j < M; j++){
						stringstream ss;
						ss << b[j];
						strb += ss.str() + " ";
					}
					map<string, int>::iterator it = p_itemset->find(strb);
					if (it == p_itemset->end()){
						continue;
					}
					else{
						p_itemset->at(strb)++;
					}
				}
			}
		}
	}

	map<string, int> first()
	{
		map<int, vector<int>>::iterator it;
		for (it = item.begin(); it != item.end(); it++){
			vector<int>::iterator it_value;
			for (it_value = it->second.begin(); it_value != it->second.end(); it_value++)
			{
				stringstream ss;
				string s;
				ss << *it_value;
				s=ss.str()+" ";
				firstitem[s] ++;
			}
		}
		map<string, int>::iterator it_L;
		for (it_L = firstitem.begin(); it_L != firstitem.end();)
		{
			if (it_L->second <= min){
				firstitem.erase(it_L++);
			}
			else{
				it_L++;
				cout << it_L->first<<endl;
			}
		}
		return firstitem;
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
	map <string, int > LL = a.CreatItem(2, L);
	map <string, int > LLL = a.CreatItem(3, LL);
	map <string,int >::iterator it;
	for (it = LLL.begin(); it != LLL.end(); it++){
		cout << "key:" << it->first<<" ";
		cout << it->second << endl;
	}
}
