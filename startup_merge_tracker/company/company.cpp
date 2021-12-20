#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];
    for (int i = 0; i < numCompanies; ++i)
        companies[i] = new Company();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    // call largest i function, and then deallocate that memory--> continue down until nullptr for merge 1 and merge 2.
    // (if statements) do this across all i's!
    for (int i = 0; i < numCompanies; i++) {
        while (largest(i) != companies[i]) {
            split(i);
        }
    }
    for (int i = 0; i < numCompanies; i++) {
        delete companies[i];
    }
    delete companies;
}

void CompanyTracker::merge(int i, int j) {
    // Create new company
    // for i and j, find largest company to which each one belongs, set each largest company's parent ptr to new
    // company, c for new company, m1=largest(i), m2=largest(j), parent=nullptr;
    if (i >= numCompanies || i < 0 || j >= numCompanies || j < 0) {
        return;
    }
    if (i == j) {
        return;
    }
    if (inSameCompany(i, j)) {
        return;
    }
    Company* c = new Company();
    c->parent = nullptr;
    c->merge1 = largest(i);
    c->merge2 = largest(j);
    largest(i)->parent = c;
    largest(j)->parent = c;
    return;
}

void CompanyTracker::split(int i) {
    if (i >= numCompanies || i < 0) {
        return;
    }
    if (largest(i) == companies[i]) {
        return;
    }

    // access m1 and m2 of the largest(i)-- make those parent ptrs point to nullptr, and then delete
    // the company, largest(i) (deallocate)
    // variables:
    Company* currLargest = largest(i);
    currLargest->merge1->parent = nullptr;
    currLargest->merge2->parent = nullptr;
    delete currLargest;
    return;
}

bool CompanyTracker::inSameCompany(int i, int j) {

    // traverse i and j's paths-- at any time, if you can find a match of pointer addresses, then
    // they're in the same company
    // for each parent of i's ancestors, check to see if it occurs in j's ancestors

    if (i >= numCompanies || i < 0 || j >= numCompanies || j < 0) {
        return false;
    }
    if (i == j) {
        return true;
    }
    Company* currP = companies[i]->parent;
    while (currP != nullptr) {
        if (hasParent(currP, j)) {
            return true;
        }
        currP = currP->parent;
    }
    return false;
    // if(hasParent(currP, j))
    //   return true
    // currP = currP->parent;
    // end while
    // return false;
}

Company* CompanyTracker::largest(int i) {
    // if companies[i] belongs to company, that belongs to company, that belongs to company, etc. until parent ==
    // nullptr,
    // create Company* parentCompany: will be used to find the next company (hierarchy). return nextCompany
    // create Company* currCompany
    // currCompany= companies[i];
    // parentCompany=currCompany->parent;
    // while(parentCompany!=nullptr)
    //   currCompany=parentCompany;
    //   parentCompany=currCompany->parent;
    // return currCompany;
    if (i < 0 || i >= numCompanies) {
        return nullptr;
    }
    Company* currCompany;
    Company* parentCompany;
    currCompany = companies[i];
    parentCompany = companies[i]->parent;
    while (parentCompany != nullptr) {
        currCompany = parentCompany;
        parentCompany = currCompany->parent;
    }
    return currCompany;
}

bool CompanyTracker::hasParent(Company* parentToTest, int baseCompany) {
    // check if parentToTest is nullptr, return false;
    // check if basecompany is between 0-numCompanies
    // start from base and check parent chain--- if parentToTest == parent
    // return true;
    // otherwise return false;
    // Company* currParent;
    // currParent= companies[baseCompany]->parent
    // while (currParent != nullptr)
    //  if ParentToTest == currParent { return true;}
    //  currParent= currparent->parent
    // after while, return false
    if (parentToTest == nullptr) {
        return false;
    }
    if (baseCompany >= (numCompanies) || baseCompany < 0) {
        return false;
    }
    Company* currParent;
    currParent = companies[baseCompany]->parent;
    while (currParent != nullptr) {
        if (currParent == parentToTest) {
            return true;
        }
        currParent = currParent->parent;
    }
    return false;
}
