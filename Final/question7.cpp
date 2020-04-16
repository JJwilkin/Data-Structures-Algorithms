#include <iostream>
#include <string>

using namespace std;

class Superhero {
    unsigned int superheroID, power_rating;
    string hero_name, power_name, origin_universe, hero_alignment; 
    friend class HeroEnsemble;
    // TODO (PART A) Fill in other required member attributes and methods below
    // Members should be declared as public or private as appropriate

    Superhero * left;
    Superhero * right;
    //since it is a binary search tree, each hero will need a pointer to their associated left and right child.

public:
    Superhero(){superheroID = 0; power_rating = 0;} 
    Superhero(unsigned int new_superheroID, unsigned int new_rating):superheroID(new_superheroID), power_rating(new_rating){}
    Superhero(unsigned int new_superheroID, unsigned int new_rating, string new_hero_name,
                string hero_power, string new_origin_universe, string new_hero_alignment): superheroID(new_superheroID), power_rating(new_rating) , hero_name(new_hero_name),power_name(hero_power), origin_universe(new_origin_universe), hero_alignment(new_hero_alignment) {}
    bool operator==(const Superhero& rhs) const { //compare ID property to ensure no duplicate entries
        return superheroID == rhs.superheroID;
    }
    bool operator<(const Superhero& rhs) const{
        return superheroID < rhs.superheroID; //BST is organized by superheroID, only usefull atributte to compare
    }
    bool operator>(const Superhero& rhs) const {
        return superheroID > rhs.superheroID;
    }
};

class HeroEnsemble {
    // TODO (PART A) Fill in other required member attributes and methods below
    // Members should be declared as public or private as appropriate
    Superhero * root;
    int size;
    //Size added to keep count of the number of heros in the HeroEnsemble
    //ADDED to reference the first or root hero node

public:
    HeroEnsemble() {root= NULL; size = 0;}
    ~HeroEnsemble();
    void destroy_tree(Superhero * root) const;
    int get_size() const;
    void print();
    Superhero * find_hero(Superhero hero) const;
    Superhero * find_parent(Superhero hero) const;
    Superhero * find_minimum (Superhero * hero) const;
    void print_helper(Superhero * root);
    bool insert_new_hero(Superhero new_hero);
    bool remove_hero(unsigned int remove_heroID);
    bool combine_superheroes(unsigned int combine_heroID);
    bool clone_superhero(unsigned int clone_heroID, unsigned int clone_count);
    bool remove_by_universe(string universe_name);
};
Superhero * HeroEnsemble:: find_minimum (Superhero * hero) const{ 
    if (size == 0) return NULL;
    Superhero * temp = hero;
    while (temp -> left) {
        temp = temp -> left;
    }
    return temp;    
}

Superhero * HeroEnsemble:: find_parent (Superhero hero) const{ 
    Superhero * temp = root;
    if (hero == *temp) return NULL; //special case, return root node if val is root
    while (temp) { //run until reach end of loop
        if ((temp->left && *temp -> left == hero) || (temp->right && *temp->right == hero)) { //if parent of desired value
            return temp;
        }
        if(hero < *temp) { //if priority is less than current node, go down left tree
            temp = temp ->left;
        }
        else if (hero > *temp) {
            temp = temp -> right;
        }

        else { //if val is not in tree
            return NULL;
        }
    }
    return NULL;

}

Superhero * HeroEnsemble:: find_hero (Superhero hero) const{
    Superhero * temp = root;
    while (temp) { //run until reach end of loop
        if(hero < *temp) { //if priority is less than current node, go down left tree
            temp = temp ->left;
        }
        else if (hero > *temp) {
            temp = temp -> right;
        }
        else if (hero == *temp) { //if priority is same, check if there is a match
            return temp;
        }
        else { //if priority is same, and description don't match, there are no matches, return false
            return NULL;
        }
    }
    return NULL;
}


HeroEnsemble::~HeroEnsemble() {
    destroy_tree(root);
}
void HeroEnsemble:: destroy_tree(Superhero * root) const {
    if (root) {
        destroy_tree(root ->left);
        destroy_tree(root ->right);
        delete root;
    }
}

void HeroEnsemble::print() {
cout << "PRINTING HEROES USING IN ORDER TRAVERSAL" << endl;
print_helper(root);
}
void HeroEnsemble::print_helper(Superhero * root) {
    if (root) {
        print_helper(root ->left);
        cout << "SUPERHERO ID: " << root -> superheroID << ", POWER RATING: " << root ->power_rating << endl;
        print_helper(root ->right);
    }
}
bool HeroEnsemble::insert_new_hero(Superhero new_hero) {
	// TODO (PART B) Insert your code here
    if (size == 0) root = new Superhero (new_hero.superheroID, new_hero.power_rating);
    else {
        Superhero * temp = root;
        while (temp) {
            if (new_hero < *temp) {
                if (!temp -> left) { //if there is no left child, set val as left child
                    temp -> left = new Superhero (new_hero.superheroID, new_hero.power_rating);
                    size++;
                    return true;
                }
                else { //if left child exist, set temp to left child and proceed to compare
                    temp = temp -> left;
                }
            }
            else if (new_hero > *temp){
                if (!temp -> right) { //if there is no right child, set val as right child
                    temp->right = new Superhero (new_hero.superheroID, new_hero.power_rating);
                    size++;
                    return true;
                }
                else { //if right child exist, set temp to right child and proceed to compare
                    temp = temp -> right;
                }
            }
            else { //reject duplicate priority
                return false;
            }
        }
    }
    size++;
    return true;
}

bool HeroEnsemble::remove_hero(unsigned int remove_heroID) {
 if (size == 0) return false;
    Superhero * target = find_hero(Superhero(remove_heroID, 0));
    if(target == NULL) return false;
    Superhero * parent = find_parent(Superhero(remove_heroID, 0));
    Superhero * temp ;
    //If val is leaf node
    //======================LEAF NODE=========================
    if (target -> left == NULL && target ->right == NULL) {
        //Check if target is left/right child of parent, then set to null
        if(parent) { //if only one node in the tree parent = NULL
            if (parent -> left == target) parent -> left = nullptr;
            else parent -> right = nullptr;
        }
        else { //if root
            root = nullptr;
        }

        size--;
        delete target;
        return true;
    }
    //=======================ONE CHILD======================
    // If node to be deleted has only one child
    if (target -> left == NULL) { //if target has right child
        //if target is left child of parent, set new left child as target's child
        if (parent) {
            if (parent -> left == target) parent -> left = target -> right;
            else parent -> right = parent ->right = target -> right;
        }
        else {//if root node
            root = target -> right;
        }
    }

    else if (target -> right == NULL){
        if(parent) {
            if (parent -> left == target) parent -> left = target -> left;
            else parent -> right = parent ->right = target -> left;
        }
        else { //if root node
            root = target -> left;
        }
    }
    //========================TWO CHILDREN=======================
    else { //If node to be delete has TWO CHILDREN
        Superhero * minimum = find_minimum(target->right);
        Superhero * minimum_parent = find_parent(*minimum);

        if (parent) { //if not root node
            if (parent->left == target) parent->left = minimum;
            else parent->right = minimum;

            if(minimum == target -> right) {
                 minimum ->left = target ->left;

            }
            else {
                if (minimum -> right) minimum_parent ->left = minimum ->right;
                else minimum_parent -> left = nullptr;

                minimum ->left = target -> left;
                minimum -> right = target -> right;
            }

        }
        else { //if root
            if(minimum == target ->right) {
                minimum ->left = root -> left;
                root = minimum;
            }
            else {
                if (minimum -> right) minimum_parent ->left = minimum ->right;
                else minimum_parent -> left = nullptr;

                minimum ->left = root -> left;
                minimum -> right = root -> right;
                root = minimum;

            }
        }
    }
    size--;
    delete target;
    return true;
}

void test_scenario1() {
	HeroEnsemble test_ensemble;
	// TODO (PART B) insert a test scenario here
	test_ensemble.insert_new_hero(Superhero(245, 10));
	test_ensemble.insert_new_hero(Superhero(137, 15,"Clever Firebird",
							"Chemistry", "UWaterloo", "Chaotic Awesome"));
    test_ensemble.insert_new_hero(Superhero(54, 104));
    test_ensemble.insert_new_hero(Superhero(65, 130));
    test_ensemble.insert_new_hero(Superhero(22, 102));                        
   Superhero batman;
    test_ensemble.insert_new_hero(batman);

		
	test_ensemble.print();	

    test_ensemble.remove_hero(0);
    test_ensemble.remove_hero(65);
    test_ensemble.remove_hero(245);
    test_ensemble.print();	
}

void test_scenario2() {
		HeroEnsemble test_ensemble;
	// TODO (PART B) insert a test scenario here
	test_ensemble.insert_new_hero(Superhero(23, 10));
	test_ensemble.insert_new_hero(Superhero(54, 15,"Clever Firebird",
							"Chemistry", "UWaterloo", "Chaotic Awesome"));
    test_ensemble.insert_new_hero(Superhero(2, 104));
    test_ensemble.insert_new_hero(Superhero(54, 130));
    test_ensemble.insert_new_hero(Superhero(3, 102));                        
   Superhero batman;
    test_ensemble.insert_new_hero(batman);

		
	test_ensemble.print();	

    test_ensemble.remove_hero(3);
    test_ensemble.remove_hero(3);
    test_ensemble.remove_hero(2);
    test_ensemble.print();	
 }
 void test_scenario3() {
	HeroEnsemble test_ensemble;
	// TODO (PART B) insert a test scenario here
	test_ensemble.insert_new_hero(Superhero(4, 10));
	test_ensemble.insert_new_hero(Superhero(77, 15,"Clever Firebird",
							"Chemistry", "UWaterloo", "Chaotic Awesome"));
    test_ensemble.insert_new_hero(Superhero(3, 104));
    test_ensemble.insert_new_hero(Superhero(243, 130));
    test_ensemble.insert_new_hero(Superhero(0, 102));                        
   Superhero batman;
    test_ensemble.insert_new_hero(batman);

		
	test_ensemble.print();	

    test_ensemble.remove_hero(0);
    test_ensemble.remove_hero(3);
    test_ensemble.remove_hero(243);
    test_ensemble.remove_hero(77);
    test_ensemble.remove_hero(4);
    test_ensemble.print();	
 }

int main() {
    // invoke the test runners
    test_scenario1();
    test_scenario2();
    test_scenario3();
}