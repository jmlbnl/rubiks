#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>


// The slow permutation class
class Permutation {
 private:
    std::vector<std::vector<int>> cycles;
    std::string name;
    Permutation(std::vector<std::vector<int>> x, std::string nm="");
    void sortedorder(std::vector<std::vector<int>> &vec);
    std::vector<std::vector<int>> pairRepresentation(std::vector<std::vector<int>> base_cycles);
    std::vector<std::vector<int>> fullRepresentation(std::vector<std::vector<int>> pairRep);
    void dump(std::vector<std::vector<int>> _cyc) { printf("%s\n", cycleString(_cyc).c_str()); }
    std::string cycleString(std::vector<std::vector<int>> _cyc);
    //std::vector<std::vector<int>> cycleIndexValues(std::vector<std::vector<int>> cyc, std::vector<std::vector<int>> idxcyc);
   
    
 public:
    static Permutation ODr, ODf, ODt;
    
    // predefined full transformations
    static Permutation Pf, Px, Pr, Pl, Pt, Pb;
    static Permutation PF, PX, PR, PL, PT, PB;

    // predefined corner transformations
    static Permutation Cf, Cx, Cr, Cl, Ct, Cb;
    static Permutation CF, CX, CR, CL, CT, CB;

    // predefined unrotated corner transformations
    static Permutation UCf, UCx, UCr, UCl, UCt, UCb;
    static Permutation UCF, UCX, UCR, UCL, UCT, UCB;

    
    Permutation(std::string cycle_string="", std::string nm="");
 
    // Note name is assembled backwards!   P("l") * P("r") ==> "rl"
    Permutation operator* (Permutation B);
    Permutation operator- ();
    
    std::string getName() { return name; }


    std::vector<int> spinToMin(std::vector<int> cyc);
    Permutation cycleIndexValues(Permutation idxcycle);
    // 1->3->2->5, 3->4->5->6, 1->4->2->6
    std::vector<std::vector<int>> cycleIndexValues(std::vector<std::vector<int>> cyc, std::vector<std::vector<int>> idxcyc);
    
    std::vector<std::vector<int>> decompose(std::vector<int> cyc);

 

    void dump() {
	printf("(%20s) (%d): ", name.c_str(), nswaps());
	dump(cycles);
    }

    void dumpPair() {
	std::vector<std::vector<int>> cyc = pairRepresentation(cycles);
	dump(cyc);
    }

    std::string dump2Str() { return cycleString(cycles); }
    std::vector<std::vector<int>> getCycles() const {	return cycles; }

    void reduceName();
    static std::string reduceName(std::string n);

    int nswaps();
  
    int getSourcePosition(int x);

    int getCycleType(std::vector<int> &x);
    int getNParity(int N);
    Permutation reduceToDegenerate();
 private:
    std::vector<int> readSingleCycle(std::string cycle_string);
};
