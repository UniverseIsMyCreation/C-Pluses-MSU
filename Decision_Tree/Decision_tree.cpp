#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <unistd.h>

#define __SUCCSED__PERCENT__ 0.1

namespace SpaceOfDecisionTree{
	enum{
		__ERROR__ = 1,
		__DEEP__MAX__ = 100,
		__NODE__VOLUME__MAX__ = 10000,
		__FIRST__CLASS__ = 0,
		__SECOND__CLASS__ = 1
	};
}

using namespace std;


//function for conveting str from file to double
double ConvertToDouble(string str){
	int number = 0;
	int after_number = 0;
	int count_after_number = 0;
	int sign = 1; 
    bool change_mode = false;
	if (str[0] == '-')
		sign = -1;
	for (int i=0;i<str.length();i++){
		if (str[i] == '-')
			continue;
		if (str[i] == '.' || str[i] == ','){
            change_mode = true;
            continue;
        }
        if (!change_mode){
		    number = number * 10 + (str[i] - '0');
        }
        if(change_mode){
            after_number = after_number * 10 + (str[i] - '0');
			count_after_number++;
        }
	}
    double multiplier = 1;
    for (int i=0;i<count_after_number;i++)
        multiplier = multiplier * 0.1;
	return (number  + multiplier*after_number)*sign;
}

//function for average value in vector(container)
double AverageOfVector(vector<vector<double>> vec, int pos){
	double sum = 0;
	double count = 0;
	for (auto iter = vec.begin(); iter != vec.end(); iter++){
		sum += (*iter)[pos];
		count++;
	}
	return sum/count;
}

//maximum in vector(container)
int MaxFromVec(vector<double> vec){
	int max_pos;
	bool put = true;
	double max;
	int count = 0;
	for (auto iter = vec.begin(); iter != vec.end(); iter++){
		if (put){
			max = *iter;
			max_pos = count;
			put = false;
		}
		else if (*iter > max){
			max = *iter;
			max_pos = count;
		}
		count++;
	}
	return max_pos;
}

//find a pos of str in vector(container)
int NumInVecStr(vector<string> vec,string aim_str){
	int count = 1;
	for (auto iter = vec.begin() + 1; iter != vec.end(); iter++){
		if (*iter == aim_str)
			break;
		count++;
	}
	return count;
}

//to save our files in form of vector of vectors
typedef struct Table_for_elements{
	vector<string> attr_names;
	vector<vector<double>> data;
	int sample_volume;
}Table;

////////////////////////////////////////////////////////////////////////////////////////

//class for getting value from incoming file
class FilesReader{
	ifstream fin;
	Table table;
public:
	FilesReader(string);
	void Parse();//get value from file, convert to table
	Table GetTable() const;// return new table
};

FilesReader::FilesReader(string filename){
	fin.open(filename);
	if(!fin){
		cout << filename << " file could not be opened" << endl;
		exit(SpaceOfDecisionTree::__ERROR__);
	}
	Parse();
}

void FilesReader::Parse(){
	string str_of_file;
	bool is_attr_name = true;
	table.sample_volume = 0;
	table.attr_names.clear();
	table.data.clear();
	while(!getline(fin, str_of_file).eof()){
		vector<string> row_str;
        vector<double> row_int;
		row_str.clear();
		row_int.clear();
		int preposition = 0;

        if (is_attr_name){
		    for(int i=0;i<str_of_file.size();i++){
			    if(str_of_file[i] == '\t') {
				    string column = str_of_file.substr(preposition, i-preposition);
				    row_str.push_back(column);
				    preposition = i+1;
			    }
		    }

            string column = str_of_file.substr(preposition, str_of_file.size()-preposition);
		    row_str.push_back(column);

			table.attr_names = row_str;
			is_attr_name = false;
        }
        else{
            for(int i=0;i<str_of_file.size();i++){
			    if(str_of_file[i] == '\t') {
				    string column = str_of_file.substr(preposition, i-preposition);
                    double number = ConvertToDouble(column);
				    row_int.push_back(number);
				    preposition = i+1;
			    }
		    }

            string column = str_of_file.substr(preposition, str_of_file.size()-preposition);
		    double number = ConvertToDouble(column);
			row_int.push_back(number);

            table.data.push_back(row_int);
			table.sample_volume++;        
        }
	}	
}

Table FilesReader::GetTable() const{
    return table;
}

////////////////////////////////////////////////////////////////////////////////////////

//Node of our DecisionTree
typedef struct Node_Tree{
    struct Node_Tree * left_predicate;
    struct Node_Tree * right_predicate;
    string attribute_name;
    double key;
	vector<vector<double>> set_of_elements;
	int cur_sample_volume;
	int deep;
	int class_ans;
}Predicate;

//class for building DecisionTree
class DecisionTree{
    Predicate * Decision_tree;
	vector<string> attr_names;//names of attributes
	int node_volume;//amount of nodes
	//int size_of_vec;//space dimension of our sample
	void BuildPredicate(Predicate *);
	bool StopBuilding(Predicate *);
	int GiveClassToNode(Predicate *) const;
	double TestPredicateScore(Predicate *,int) const;
	double TestPredicatePrediction(Predicate *,int) const;
	void PushBestScore(Predicate *, int) const;
	bool TestRightList(Predicate *, vector<double>) const;
	void DeletePredicate(Predicate *);
public:
    DecisionTree(Table);
	double Test(Table) const;
	~DecisionTree();
};

void DecisionTree::DeletePredicate(Predicate * predicate){
	if (predicate == nullptr)
		return;
	DeletePredicate(predicate->left_predicate);
	DeletePredicate(predicate->right_predicate);
	delete predicate;
} 

DecisionTree::~DecisionTree(){
	DeletePredicate(Decision_tree->left_predicate);
	DeletePredicate(Decision_tree->right_predicate);
	delete Decision_tree;
}

//start to build our DecisionTree
DecisionTree::DecisionTree(Table table){
	Decision_tree = new Predicate;
	Decision_tree->deep = 1;
	Decision_tree->cur_sample_volume = table.sample_volume;
	Decision_tree->set_of_elements = table.data;
	Decision_tree->left_predicate = nullptr;
	Decision_tree->right_predicate = nullptr;
	this->attr_names = table.attr_names;
	node_volume = 1;
	//size_of_vec = Decision_tree->set_of_elements[0].size() - 1;
	Decision_tree->class_ans = -1;
	BuildPredicate(Decision_tree);
}

//find out which class must be in node
int DecisionTree::GiveClassToNode(Predicate * predicate) const{
	int amount_of_first_class = 0;
	int amount_of_second_class = 0;
	//int size_of_set = predicate->set_of_elements[0].size() - 1;
	for (auto iter_set = predicate->set_of_elements.begin();iter_set != predicate->set_of_elements.end();iter_set++){
		if((*iter_set)[0] == SpaceOfDecisionTree::__FIRST__CLASS__)
			amount_of_first_class++;
		else
			amount_of_second_class++;
	}

	if (amount_of_first_class > amount_of_second_class)
		return SpaceOfDecisionTree::__FIRST__CLASS__;
	else
		return SpaceOfDecisionTree::__SECOND__CLASS__;
}

//condition to stop to build our nodes in this branch
bool DecisionTree::StopBuilding(Predicate * predicate){
	if (predicate->deep >= SpaceOfDecisionTree::__DEEP__MAX__)
		return true;
	node_volume++;
	if (node_volume > SpaceOfDecisionTree::__NODE__VOLUME__MAX__){
		node_volume--;
		return true;
	}

	double amount_of_first_class = 0;
	double amount_of_second_class = 0;
	for (auto iter_set = predicate->set_of_elements.begin();iter_set != predicate->set_of_elements.end();iter_set++){
		if((*iter_set)[0] == SpaceOfDecisionTree::__FIRST__CLASS__)
			amount_of_first_class++;
		else
			amount_of_second_class++;
	}

	if (amount_of_first_class == 0)
		return true;
	if (amount_of_second_class == 0)
		return true;

	double first_relation = amount_of_first_class/amount_of_second_class;
	double second_relation = amount_of_second_class/amount_of_first_class;

	if (second_relation < __SUCCSED__PERCENT__)
		return true;
	if (first_relation < __SUCCSED__PERCENT__)
		return true;
	return false;
}

//building new nodes according best score of our prediction
void DecisionTree::PushBestScore(Predicate * predicate, int best_pos) const{
	predicate->attribute_name = attr_names[best_pos];
	predicate->key = AverageOfVector(predicate->set_of_elements,best_pos);
	predicate->right_predicate->cur_sample_volume = 0;
	predicate->left_predicate->cur_sample_volume = 0;
	
	for (auto iter = predicate->set_of_elements.begin(); iter != predicate->set_of_elements.end();iter++){
		if ((*iter)[best_pos] > predicate->key){
			predicate->right_predicate->set_of_elements.push_back(*iter);
			predicate->right_predicate->cur_sample_volume++;
		}
		else{
			predicate->left_predicate->set_of_elements.push_back(*iter);
			predicate->left_predicate->cur_sample_volume++;
		}
	}

	predicate->left_predicate->deep = predicate->deep + 1;
	predicate->right_predicate->deep = predicate->deep + 1;
	predicate->left_predicate->class_ans = -1;
	predicate->right_predicate->class_ans = -1;
}

//check the score of our prediction
double DecisionTree::TestPredicatePrediction(Predicate * predicate, int Class) const{
	double count = 0;
	double count_of_right_predictions = 0;
	for (auto iter = predicate->set_of_elements.begin();iter != predicate->set_of_elements.end();iter++){
		count++;
		if ((*iter)[0] == Class)
			count_of_right_predictions++;
	}
	return count_of_right_predictions/count;	
}

//estimate our predictions
double DecisionTree::TestPredicateScore(Predicate * predicate, int count) const{
	for (auto iter = predicate->set_of_elements.begin(); iter != predicate->set_of_elements.end(); iter++){
		if ((*iter)[count] > predicate->key)
			predicate->right_predicate->set_of_elements.push_back(*iter);
		else
			predicate->left_predicate->set_of_elements.push_back(*iter);
	}

	double estimate1 = TestPredicatePrediction(predicate->left_predicate, SpaceOfDecisionTree::__FIRST__CLASS__);
	estimate1+= TestPredicatePrediction(predicate->right_predicate, SpaceOfDecisionTree::__SECOND__CLASS__);
	double estimate2 = TestPredicatePrediction(predicate->right_predicate, SpaceOfDecisionTree::__FIRST__CLASS__);
	estimate2 += TestPredicatePrediction(predicate->left_predicate, SpaceOfDecisionTree::__SECOND__CLASS__);
	if (estimate1 > estimate2)
		return estimate1;
	else
		return estimate2;
}

//build new nodes
void DecisionTree::BuildPredicate(Predicate * predicate){
	
	if (StopBuilding(predicate)){
		predicate->class_ans = GiveClassToNode(predicate);
		predicate->set_of_elements.clear();
		predicate->cur_sample_volume = 0;
		predicate->left_predicate = nullptr;
		predicate->right_predicate = nullptr;
		return;
	}

	predicate->left_predicate = new Predicate;
	predicate->right_predicate = new Predicate;
	predicate->right_predicate->set_of_elements.clear();
	predicate->left_predicate->set_of_elements.clear();
	
	int count = 1;
	vector<double> score_of_attrs;
	score_of_attrs.clear();
	for (auto iter_attr_name = attr_names.begin() + 1; iter_attr_name != attr_names.end(); iter_attr_name++){
		predicate->key = AverageOfVector(predicate->set_of_elements,count);
		score_of_attrs.push_back(TestPredicateScore(predicate,count));
		predicate->right_predicate->set_of_elements.clear();
		predicate->left_predicate->set_of_elements.clear();
		count++;
	}
	int best_pos_of_prediction = MaxFromVec(score_of_attrs) + 1; 
	PushBestScore(predicate, best_pos_of_prediction);
	BuildPredicate(predicate->left_predicate);
	BuildPredicate(predicate->right_predicate);
}

//check the accuracy of our built DecisionTree
double DecisionTree::Test(Table table) const{
	double right_prediction = 0;
	for (auto iter = table.data.begin(); iter != table.data.end(); iter++){
		if(TestRightList(Decision_tree,*iter))
			right_prediction++;
	}
	return right_prediction/table.sample_volume;
}

//descend to the leafs and find out which class out object from sample will get
bool DecisionTree::TestRightList(Predicate * predicate, vector<double> aim_vec) const{
	if (predicate->class_ans != -1){
		if (aim_vec[0] == predicate->class_ans)
			return true;
		else
			return false;
	}
	int pos = NumInVecStr(attr_names,predicate->attribute_name);
	if (aim_vec[pos] > predicate->key)
		return TestRightList(predicate->right_predicate,aim_vec);
	else
		return TestRightList(predicate->left_predicate,aim_vec);
}

////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){
    if (argc != 3){
        cout << "Not enough arguments for building Decision Tree" << endl;
        exit(SpaceOfDecisionTree::__ERROR__);
    }
    
    string file_train = argv[1];
	FilesReader Reader_of_train(file_train);
    DecisionTree Answer_tree(Reader_of_train.GetTable());

	string file_test = argv[2];
	FilesReader Reader_of_test(file_test);
	cout << "Accuracy is: " << Answer_tree.Test(Reader_of_test.GetTable()) << endl;

    return 0;
}