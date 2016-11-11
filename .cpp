//
//  main.cpp
//  Optimal Strats Game Pick from two ends DP
//
//  Created by Zijian Xie on 2016/11/11.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//  N pots, each with some number of gold coins, are arranged in a line. You are playing a game against another player. You take turns picking a pot of gold. You may pick a pot from either end of the line, remove the pot, and keep the gold pieces. The player with the most gold at the end wins. Develop a strategy for playing this game.
//  也就是说每次你只能从两端来取数

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
using namespace std;

class OptimalStrats{
private:
    vector<int> nums;
public:
    OptimalStrats(vector<int> nums){
        this->nums = nums;
    }
    int DP(){
        int n = (int) nums.size();
        vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(n));
        for(int i = 0; i < n; ++i){
            dp[i][i].first = nums[i];
            dp[i][i].second = 0;
        }
        
        for(int len = 2; len <= n; ++len){
            for(int i = 0; i + len <= n; ++i){
                int j = i + len - 1;
                //以i 或者 j 为1的初始选择的点（因为只能选择两头），那么剩下的最大的那个value就是2得到的。
                //for player 1, we could choose from i or j - 1(because we could only choose an element from two ends, and the rest max value will be the player 2's gain.)
                //这里的second就代表在2选完后，1还能选择的最大价值， 也就是1和2交换了。现在2成了first，1成了second
                // so we will ".second" as the max value player 1 can choose after 2 finish his choosing.
                if((i+1 < n ? dp[i+1][j].second : 0 ) + nums[i] > (j > 0 ? dp[i][j-1].second : 0) + nums[j]){
                    dp[i][j].first = dp[i+1][j].second + nums[i];
                    dp[i][j].second = dp[i+1][j].first;
                }else{
                    dp[i][j].first = dp[i][j-1].second + nums[j];
                    dp[i][j].second = dp[i][j-1].first;
                }
            }
        }
        cout<<"The result is: Player 1: "<<dp[0][n-1].first<<", Player 2: "<<dp[0][n-1].second<<". "<<endl;
        return dp[0][n-1].first;
    }
};


int main(int argc, const char * argv[]) {
    vector<int> nums = {3,9,1,2};
    OptimalStrats* test = new OptimalStrats(nums);
    test->DP();
    return 0;
}
/*
The result is: Player 1: 11, Player 2: 4. 
Program ended with exit code: 0
*/
