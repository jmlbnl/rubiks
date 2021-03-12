#include "PermutationMap.h"

PermutationMap::PermutationMap(int n, Face *array) {
    std::vector<Face> faces;
    for(int i=0;i<n;i++) {
	faces.push_back(array[i]);
    }
    std::sort(faces.begin(), faces.end(), [](const Face &a, const Face &b) { return (a.id < b.id); });
    
    for(int idx=0;idx<n;idx++) {
	int lab = faces[idx].id;
	
	idx2label.insert({ idx, lab });
	label2idx.insert({ lab, idx });
	
	if(lab > 100) {
	  c_idx2label.insert({ idx, lab });
	  c_label2idx.insert({ lab, idx });
	}
	else if (lab > 10) {
	  s_idx2label.insert({ idx, lab });
	  s_label2idx.insert({ lab, idx });
	}
    }
    
    face_opposites.insert({{1,2}, {2,1}, {3,5}, {4,6}, {5,3}, {6,4}});
    c_label_clockwise.insert({
			      {134,314},{314,413},{413,134},
			      {145,415},{415,514},{514,145},
			      {156,516},{516,615},{615,156},
			      {136,613},{613,316},{316,136},
			      {234,423},{423,324},{324,234},
			      {236,326},{326,623},{623,236},
			      {256,625},{625,526},{526,256},
			      {245,524},{524,425},{425,245}
      });
    
    s_label_opposites.insert({
			      {13,31},{31,13},
			      {14,41},{41,14},
			      {15,51},{51,15},
			      {16,61},{61,16},
			      {23,32},{32,23},
			      {24,42},{42,24},
			      {25,52},{52,25},
			      {26,62},{62,26},
			      {34,43},{43,34},
			      {36,63},{63,36},
			      {56,65},{65,56},
			      {45,54},{54,45}
      });
    
    // printf("here\n");
    if(n == 48) {
	// Corner Cubies
	std::vector<int> cubieIdx2Face = { 134, 136, 145, 156, 234, 236, 245, 256 };
	for(int ccIdx=0;ccIdx<8;ccIdx++) {
	    cornercubies.ccIdx2Idx[ccIdx] = label2idx.at(cubieIdx2Face[ccIdx]);
	}
	for(int idx=0;idx<48;idx++) {
	    int face = idx2label.at(idx);
	    if(face < 100) continue;                   // only corners!
	    
	    int sampleface = sortDigits(face);         // choose the sample digit!
	    int ccIdx = 0;
	    for(ccIdx = 0;;ccIdx++) {
		if(cubieIdx2Face[ccIdx] == sampleface) break;
	    }
	    cornercubies.idx2ccIdx[idx] = ccIdx;
	}
	for(int ccIdx=0;ccIdx<8;ccIdx++) {
	    int locIdx = cornercubies.ccIdx2Idx[ccIdx];
	    for(int faceIdx=0;faceIdx<48;faceIdx++) {
		int loc = idx2label.at(locIdx);
		if(loc < 100) continue;                // only corners!
		int face = idx2label.at(faceIdx);
	    
		cornercubies.face2Orientation[ccIdx][faceIdx] = getCornerOrientation(loc, face);
	    }
	}

	//	printf("there\n");
	// sides...
	std::vector<int> sideIdx2Face = { 13, 34, 23, 36, 14, 16, 24, 26, 15, 45, 25, 56 };
	for(int ccIdx=0;ccIdx<12;ccIdx++) {
	    sidecubies.ccIdx2Idx[ccIdx] = label2idx.at(sideIdx2Face[ccIdx]);
	}
	for(int idx=0;idx<48;idx++) {
	    int face = idx2label.at(idx);
	    if((face < 10) || (face > 100)) continue;

	    int sampleface = sortDigits(face);
	    int ccIdx = 0;
	    for(ccIdx = 0;;ccIdx++) {
		if(sideIdx2Face[ccIdx] == sampleface) break;
	    }
	    sidecubies.idx2ccIdx[idx] = ccIdx;
	}
	for(int ccIdx=0;ccIdx<12;ccIdx++) {
	    // printf("ccc %d\n",ccIdx);
	    int locIdx = sidecubies.ccIdx2Idx[ccIdx];
	    for(int faceIdx=0;faceIdx<48;faceIdx++) {
		//	printf("ddd %d\n", faceIdx);
		int loc = idx2label.at(locIdx);
		if((loc < 10) || (loc > 100)) continue;
		int face = idx2label.at(faceIdx);
		int orient = 0;
		if(face == sortDigits(face)) {
		    orient = 1;
		}
		
		sidecubies.face2Orientation[ccIdx][faceIdx] = orient;
		//	printf("orient: loc=%d face=%d orient=%d\n", loc, face, orient);
	    }
	}
    }
}

void PermutationMap::dump() {
    printf("idx2label.size() = %lu     label2idx.size() = %lu\n", idx2label.size(), label2idx.size());
    for(int i=0;i<idx2label.size();i++) {
	printf("idx2label[%d] = %d       label2idx[%d] = %d\n", i, idx2label.at(i), idx2label.at(i), label2idx.at(idx2label.at(i)));
    }
}

// A clockwise turn increases the orientation value by 1!
//
// 134@134,  314@314, 413@413  --> o = 0
// 413@134,  134@314, 314@413  --> o = 1
// 314@134,  413@314, 134@413  --> o = 2
//
// get the orientation of the cubie connected in position pos, with face at pos.
int PermutationMap::getCornerOrientation(int pos, int face) {
    int o_of_pos = 0;
    int o_of_face = 0;

    int oface = face;
    int opos = pos;
    while(pos/100 > 2) {
	pos = c_label_clockwise.at(pos);
	o_of_pos++;
    }
    while(face/100 > 2) {
	face = c_label_clockwise.at(face);
	o_of_face++;
    }

    int o = ((3 + o_of_face - o_of_pos + 3) % 3);
    //printf("corner orientation:  %d @ %d = %d  {%d %d}\n", oface, opos, o, o_of_pos, o_of_face);
    return ((3 + o_of_face - o_of_pos) % 3); 
}

int PermutationMap::getSideOrientation(int pos, int face) {
    std::vector<int> marked_sides = { 13, 14, 15, 16, 23, 24, 25, 26, 43, 45, 63, 65 };

    bool p_marked = std::binary_search(marked_sides.begin(), marked_sides.end(), pos);
    bool f_marked = std::binary_search(marked_sides.begin(), marked_sides.end(), face);

    int o =1;
    if(p_marked == f_marked) o=0;
    //printf("side orientation: %d @ %d = %d\n", face, pos, o);
    return o;

}

int PermutationMap::sortDigits(int x) {
    std::vector<int> digits;
    while(x) {
	int digit = x % 10;
	digits.push_back(digit);
	x /= 10;
    }
    std::sort(digits.begin(), digits.end(), std::greater<int>());
    int y = 0;
    while(digits.size() > 0) {
       	y = y*10 + digits.back();
	digits.pop_back();
    }

    return y;
}

int PermutationMap::flipDigits(int x) {
    std::vector<int> digits;
    while(x) {
	int digit = x % 10;
	digits.push_back(digit);
	x/=10;
    }
    int y=0;
    for(auto i : digits) {
	y = y*10 + i;
    }
    return y;
}

Face DisplayFaces[54] = {
    { 156, 0,0 }, { 15,  1,0 }, { 145, 2,0 }, { 16,  0,1 }, { 1,   1,1 }, { 14,  2,1 }, { 136, 0,2 }, { 13,  1,2 }, { 134, 2,2 },
    { 256, 2,0 }, { 25,  1,0 }, { 245, 0,0 }, { 26,  2,1 }, { 2,   1,1 }, { 24,  0,1 }, { 236, 2,2 }, { 23,  1,2 }, { 234, 0,2 },
    { 326, 0,0 }, { 36,  1,0 }, { 316, 2,0 }, { 32,  0,1 }, { 3,   1,1 }, { 31,  2,1 }, { 324, 0,2 }, { 34,  1,2 }, { 314, 2,2 },
    { 415, 0,0 }, { 45,  1,0 }, { 425, 2,0 }, { 41,  0,1 }, { 4,   1,1 }, { 42,  2,1 }, { 413, 0,2 }, { 43,  1,2 }, { 423, 2,2 },
    { 516, 0,0 }, { 51,  0,1 }, { 514, 0,2 }, { 56,  1,0 }, { 5,   1,1 }, { 54,  1,2 }, { 526, 2,0 }, { 52,  2,1 }, { 524, 2,2 },
    { 615, 0,0 }, { 65,  0,1 }, { 625, 0,2 }, { 61,  1,0 }, { 6,   1,1 }, { 62,  1,2 }, { 613, 2,0 }, { 63,  2,1 }, { 623, 2,2 } 
};

static Face FacesFull[48] = {
    { 156, 0,0 }, { 15,  1,0 }, { 145, 2,0 }, { 16,  0,1 }, { 14,  2,1 }, { 136, 0,2 }, { 13,  1,2 }, { 134, 2,2 },
    { 256, 2,0 }, { 25,  1,0 }, { 245, 0,0 }, { 26,  2,1 }, { 24,  0,1 }, { 236, 2,2 }, { 23,  1,2 }, { 234, 0,2 },
    { 326, 0,0 }, { 36,  1,0 }, { 316, 2,0 }, { 32,  0,1 }, { 31,  2,1 }, { 324, 0,2 }, { 34,  1,2 }, { 314, 2,2 },
    { 415, 0,0 }, { 45,  1,0 }, { 425, 2,0 }, { 41,  0,1 }, { 42,  2,1 }, { 413, 0,2 }, { 43,  1,2 }, { 423, 2,2 },
    { 516, 0,0 }, { 51,  0,1 }, { 514, 0,2 }, { 56,  1,0 }, { 54,  1,2 }, { 526, 2,0 }, { 52,  2,1 }, { 524, 2,2 },
    { 615, 0,0 }, { 65,  0,1 }, { 625, 0,2 }, { 61,  1,0 }, { 62,  1,2 }, { 613, 2,0 }, { 63,  2,1 }, { 623, 2,2 } 
};

static Face FacesCorners[24] = {
    { 156, 0,0 }, { 145, 2,0 }, { 136, 0,2 }, { 134, 2,2 },
    { 256, 2,0 }, { 245, 0,0 }, { 236, 2,2 }, { 234, 0,2 },
    { 326, 0,0 }, { 316, 2,0 }, { 324, 0,2 }, { 314, 2,2 },
    { 415, 0,0 }, { 425, 2,0 }, { 413, 0,2 }, { 423, 2,2 },
    { 516, 0,0 }, { 514, 0,2 }, { 526, 2,0 }, { 524, 2,2 },
    { 615, 0,0 }, { 625, 0,2 }, { 613, 2,0 }, { 623, 2,2 } 
};

static Face FacesUnrotatedCorners[8] = {
    { 136, 0,0 }, { 134, 2,0 }, { 156, 0,2 }, { 145, 2,2 },
    { 234, 2,0 }, { 236, 0,0 }, { 245, 2,2 }, { 256, 0,2 }
};

PermutationMap RubiksMap(48, FacesFull);
PermutationMap CubeMapCorners(24, FacesCorners);
PermutationMap CubeMapUnrotatedCorners(8, FacesUnrotatedCorners);
