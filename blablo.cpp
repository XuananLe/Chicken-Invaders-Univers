    #include <iostream>
    #include <string>
    #include <random>
    #include <ctime>
    using namespace std;

    void generate_binary_combinations(int n, string current) {
        if (n == 0) {
            cout << current << endl;
        } else {
            generate_binary_combinations(n - 1, current + "0");
            generate_binary_combinations(n - 1, current + "1");
        }
    }

int main() 
{
    srand(time(NULL)); // seed the random number generator with the current time

    for(int i = 0; i < 10; i++)
    {
        int rand_num = rand() % 100 + 1;
        cout << rand_num << endl;
    }
    
    return 0;
}
