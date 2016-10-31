/*Author: Jennifer Mendoza
* Description: function definitions
* Group: Fandango
* Last Modified: 10/30/2016
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "feature.hpp"
#include "item.hpp"

Feature::Feature(string f1, string fdesc, string req, string haveReq)
{
	name=f1;
	desc=fdesc;
	dependency=req;
	reqDesc=haveReq;
}

//checks to see if the required item is in backpack
//returns either main description or unique description
string Feature::getDesc(vector<Item> &checkBackpack)
{
	vector<Item>::iterator Iter;
	for (Iter = checkBackpack.begin(); Iter != checkBackpack.end(); ++Iter)
	{
		if(Iter->name.compare(dependency)==0)
		{
			return reqDesc;
		}			
	}
	return desc;
}

string Feature::getFeatureName()
{
	return name;
}
