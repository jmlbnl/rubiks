#include "PermutationMap.h"

PermutationMap::PermutationMap(int n, Face *array) {
    std::vector<Face> faces;
    for(int i=0;i<n;i++) {
	faces.push_back(array[i]);
    }
    std::sort(faces.begin(), faces.end(), [](Face &a, Face &b) { return (a.id < b.id); });
    
    for(int i=0;i<n;i++) {
	idx2label.insert({ i, faces[i].id });
	label2idx.insert({faces[i].id, i });
    }

    // build corner indeces
    ncorners=0;
    nsides=0;
    for(int i=0;i<n;i++) {
	int id = idx2label.at(i);
	if(id > 100) {
	    cornerIdx[ncorners] = i;
	    ncorners++;
	}
	else if (id > 10) {
	    sideIdx[nsides] = i;
	    nsides++;
	}
    }

    //printf("nsides = %d\n", nsides);
    //printf("ncorners = %d\n", ncorners);
	    
}

void PermutationMap::dump() {
    printf("idx2label.size() = %lu     label2idx.size() = %lu\n", idx2label.size(), label2idx.size());
    for(int i=0;i<idx2label.size();i++) {
	printf("idx2label[%d] = %d       label2idx[%d] = %d\n", i, idx2label.at(i), idx2label.at(i), label2idx.at(idx2label.at(i)));
    }
}

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
