xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}


Frame Scene_Root {
 

 Frame cube1 {
  

  FrameTransformMatrix {
   0.340766,0.000000,0.000000,0.000000,0.000000,0.030690,0.000000,0.000000,0.000000,0.000000,0.424241,0.000000,0.000000,0.141427,0.000000,1.000000;;
  }

  Mesh cube1_obj {
   36;
   -0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;0.000000;-0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;0.000000;0.500000;,
   -0.500000;0.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   -0.500000;1.000000;0.500000;,
   -0.500000;0.000000;-0.500000;,
   -0.500000;1.000000;0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;0.000000;-0.500000;,
   0.500000;1.000000;-0.500000;,
   0.500000;1.000000;0.500000;,
   0.500000;0.000000;-0.500000;,
   0.500000;1.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   -0.500000;1.000000;-0.500000;,
   -0.500000;1.000000;0.500000;,
   0.500000;1.000000;0.500000;,
   -0.500000;1.000000;-0.500000;,
   0.500000;1.000000;0.500000;,
   0.500000;1.000000;-0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;0.000000;0.500000;,
   0.500000;1.000000;0.500000;,
   -0.500000;0.000000;0.500000;,
   0.500000;1.000000;0.500000;,
   -0.500000;1.000000;0.500000;;
   12;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshTextureCoords {
    36;
    -0.156850;-0.004150;,
    -0.156850;-0.344150;,
    -0.004836;-0.344954;,
    -0.156850;-0.004150;,
    -0.004836;-0.344954;,
    -0.004836;-0.004954;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    -1.000000;-0.340000;,
    0.000000;0.000000;,
    -1.000000;-0.340000;,
    0.000000;-0.340000;,
    -0.004836;-0.004954;,
    -0.156850;-0.004150;,
    -0.156850;-0.344150;,
    -0.004836;-0.004954;,
    -0.156850;-0.344150;,
    -0.004836;-0.344954;,
    -0.156850;-0.004150;,
    -0.156850;-0.344150;,
    -0.004836;-0.344954;,
    -0.156850;-0.004150;,
    -0.004836;-0.344954;,
    -0.004836;-0.004954;,
    0.000000;-0.340000;,
    0.000000;0.000000;,
    -1.000000;0.000000;,
    0.000000;-0.340000;,
    -1.000000;0.000000;,
    -1.000000;-0.340000;,
    -0.004836;-0.004954;,
    -0.156850;-0.004150;,
    -0.156850;-0.344150;,
    -0.004836;-0.004954;,
    -0.156850;-0.344150;,
    -0.004836;-0.344954;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Material1 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "taijukei.bmp";
     }
    }
   }
  }
 }

 Frame cube2 {
  

  FrameTransformMatrix {
   0.087043,0.000000,0.000000,0.000000,0.000000,0.811310,0.000000,0.000000,0.000000,0.000000,0.059149,0.000000,0.000000,0.000000,-0.332272,1.000000;;
  }

  Mesh cube2_obj {
   36;
   -0.500000;0.000000;0.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;0.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   -0.500000;0.000000;1.000000;,
   -0.500000;1.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   -0.500000;1.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   -0.500000;1.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;1.000000;0.000000;,
   -0.500000;0.000000;1.000000;,
   0.500000;0.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;0.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;1.000000;1.000000;;
   12;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshTextureCoords {
    36;
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Material2 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "taijukei.bmp";
     }
    }
   }
  }
 }

 Frame cylinder {
  

  FrameTransformMatrix {
   0.243055,0.000000,0.000000,0.000000,0.000000,-0.000000,0.086494,0.000000,0.000000,-0.243055,-0.000000,0.000000,0.000000,0.821695,-0.303310,1.000000;;
  }

  Mesh cylinder_obj {
   96;
   -0.707107;-0.500000;0.707107;,
   -1.000000;-0.500000;0.000000;,
   0.000000;-0.500000;0.000000;,
   -1.000000;-0.500000;0.000000;,
   -0.707107;-0.500000;0.707107;,
   -0.707107;0.500000;0.707107;,
   -1.000000;-0.500000;0.000000;,
   -0.707107;0.500000;0.707107;,
   -1.000000;0.500000;0.000000;,
   -1.000000;0.500000;0.000000;,
   -0.707107;0.500000;0.707107;,
   0.000000;0.500000;0.000000;,
   0.000000;-0.500000;1.000000;,
   -0.707107;-0.500000;0.707107;,
   0.000000;-0.500000;0.000000;,
   -0.707107;-0.500000;0.707107;,
   0.000000;-0.500000;1.000000;,
   0.000000;0.500000;1.000000;,
   -0.707107;-0.500000;0.707107;,
   0.000000;0.500000;1.000000;,
   -0.707107;0.500000;0.707107;,
   -0.707107;0.500000;0.707107;,
   0.000000;0.500000;1.000000;,
   0.000000;0.500000;0.000000;,
   0.707107;-0.500000;0.707107;,
   0.000000;-0.500000;1.000000;,
   0.000000;-0.500000;0.000000;,
   0.000000;-0.500000;1.000000;,
   0.707107;-0.500000;0.707107;,
   0.707107;0.500000;0.707107;,
   0.000000;-0.500000;1.000000;,
   0.707107;0.500000;0.707107;,
   0.000000;0.500000;1.000000;,
   0.000000;0.500000;1.000000;,
   0.707107;0.500000;0.707107;,
   0.000000;0.500000;0.000000;,
   1.000000;-0.500000;0.000000;,
   0.707107;-0.500000;0.707107;,
   0.000000;-0.500000;0.000000;,
   0.707107;-0.500000;0.707107;,
   1.000000;-0.500000;0.000000;,
   1.000000;0.500000;0.000000;,
   0.707107;-0.500000;0.707107;,
   1.000000;0.500000;0.000000;,
   0.707107;0.500000;0.707107;,
   0.707107;0.500000;0.707107;,
   1.000000;0.500000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.707107;-0.500000;-0.707107;,
   1.000000;-0.500000;0.000000;,
   0.000000;-0.500000;0.000000;,
   1.000000;-0.500000;0.000000;,
   0.707107;-0.500000;-0.707107;,
   0.707107;0.500000;-0.707107;,
   1.000000;-0.500000;0.000000;,
   0.707107;0.500000;-0.707107;,
   1.000000;0.500000;0.000000;,
   1.000000;0.500000;0.000000;,
   0.707107;0.500000;-0.707107;,
   0.000000;0.500000;0.000000;,
   0.000000;-0.500000;-1.000000;,
   0.707107;-0.500000;-0.707107;,
   0.000000;-0.500000;0.000000;,
   0.707107;-0.500000;-0.707107;,
   0.000000;-0.500000;-1.000000;,
   0.000000;0.500000;-1.000000;,
   0.707107;-0.500000;-0.707107;,
   0.000000;0.500000;-1.000000;,
   0.707107;0.500000;-0.707107;,
   0.707107;0.500000;-0.707107;,
   0.000000;0.500000;-1.000000;,
   0.000000;0.500000;0.000000;,
   -0.707107;-0.500000;-0.707107;,
   0.000000;-0.500000;-1.000000;,
   0.000000;-0.500000;0.000000;,
   0.000000;-0.500000;-1.000000;,
   -0.707107;-0.500000;-0.707107;,
   -0.707107;0.500000;-0.707107;,
   0.000000;-0.500000;-1.000000;,
   -0.707107;0.500000;-0.707107;,
   0.000000;0.500000;-1.000000;,
   0.000000;0.500000;-1.000000;,
   -0.707107;0.500000;-0.707107;,
   0.000000;0.500000;0.000000;,
   -1.000000;-0.500000;0.000000;,
   -0.707107;-0.500000;-0.707107;,
   0.000000;-0.500000;0.000000;,
   -0.707107;-0.500000;-0.707107;,
   -1.000000;-0.500000;0.000000;,
   -1.000000;0.500000;0.000000;,
   -0.707107;-0.500000;-0.707107;,
   -1.000000;0.500000;0.000000;,
   -0.707107;0.500000;-0.707107;,
   -0.707107;0.500000;-0.707107;,
   -1.000000;0.500000;0.000000;,
   0.000000;0.500000;0.000000;;
   32;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;,
   3;36,37,38;,
   3;39,40,41;,
   3;42,43,44;,
   3;45,46,47;,
   3;48,49,50;,
   3;51,52,53;,
   3;54,55,56;,
   3;57,58,59;,
   3;60,61,62;,
   3;63,64,65;,
   3;66,67,68;,
   3;69,70,71;,
   3;72,73,74;,
   3;75,76,77;,
   3;78,79,80;,
   3;81,82,83;,
   3;84,85,86;,
   3;87,88,89;,
   3;90,91,92;,
   3;93,94,95;;

   MeshNormals {
    96;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    -0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;0.000000;-1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    -1.000000;0.000000;0.000000;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;;
    32;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;;
   }

   MeshTextureCoords {
    96;
    -0.816874;-0.701606;,
    -0.793834;-0.645983;,
    -0.872497;-0.645983;,
    -0.242756;-0.370000;,
    -0.367756;-0.370000;,
    -0.367756;-0.450000;,
    -0.242756;-0.370000;,
    -0.367756;-0.450000;,
    -0.242756;-0.450000;,
    -0.221831;-0.718625;,
    -0.303678;-0.521029;,
    -0.501274;-0.718625;,
    -0.872497;-0.724646;,
    -0.816874;-0.701606;,
    -0.872497;-0.645983;,
    -0.367756;-0.370000;,
    -0.492756;-0.370000;,
    -0.492756;-0.450000;,
    -0.367756;-0.370000;,
    -0.492756;-0.450000;,
    -0.367756;-0.450000;,
    -0.303678;-0.521029;,
    -0.501274;-0.439182;,
    -0.501274;-0.718625;,
    -0.928120;-0.701606;,
    -0.872497;-0.724646;,
    -0.872497;-0.645983;,
    -0.492756;-0.370000;,
    -0.617756;-0.370000;,
    -0.617756;-0.450000;,
    -0.492756;-0.370000;,
    -0.617756;-0.450000;,
    -0.492756;-0.450000;,
    -0.501274;-0.439182;,
    -0.698870;-0.521029;,
    -0.501274;-0.718625;,
    -0.951160;-0.645983;,
    -0.928120;-0.701606;,
    -0.872497;-0.645983;,
    -0.617756;-0.370000;,
    -0.742756;-0.370000;,
    -0.742756;-0.450000;,
    -0.617756;-0.370000;,
    -0.742756;-0.450000;,
    -0.617756;-0.450000;,
    -0.698870;-0.521029;,
    -0.780717;-0.718625;,
    -0.501274;-0.718625;,
    -0.928120;-0.590360;,
    -0.951160;-0.645983;,
    -0.872497;-0.645983;,
    -0.742756;-0.370000;,
    -0.867756;-0.370000;,
    -0.867756;-0.450000;,
    -0.742756;-0.370000;,
    -0.867756;-0.450000;,
    -0.742756;-0.450000;,
    -0.780717;-0.718625;,
    -0.698870;-0.916221;,
    -0.501274;-0.718625;,
    -0.872497;-0.567320;,
    -0.928120;-0.590360;,
    -0.872497;-0.645983;,
    -0.867756;-0.370000;,
    -0.992756;-0.370000;,
    -0.992756;-0.450000;,
    -0.867756;-0.370000;,
    -0.992756;-0.450000;,
    -0.867756;-0.450000;,
    -0.698870;-0.916221;,
    -0.501274;-0.998068;,
    -0.501274;-0.718625;,
    -0.816874;-0.590360;,
    -0.872497;-0.567320;,
    -0.872497;-0.645983;,
    0.007244;-0.370000;,
    -0.117756;-0.370000;,
    -0.117756;-0.450000;,
    0.007244;-0.370000;,
    -0.117756;-0.450000;,
    0.007244;-0.450000;,
    -0.501274;-0.998068;,
    -0.303678;-0.916221;,
    -0.501274;-0.718625;,
    -0.793834;-0.645983;,
    -0.816874;-0.590360;,
    -0.872497;-0.645983;,
    -0.117756;-0.370000;,
    -0.242756;-0.370000;,
    -0.242756;-0.450000;,
    -0.117756;-0.370000;,
    -0.242756;-0.450000;,
    -0.117756;-0.450000;,
    -0.303678;-0.916221;,
    -0.221831;-0.718625;,
    -0.501274;-0.718625;;
   }

   MeshMaterialList {
    1;
    32;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Material {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "taijukei.bmp";
     }
    }
   }
  }
 }

 Frame cube3 {
  

  FrameTransformMatrix {
   0.370100,0.000000,0.000000,0.000000,0.000000,0.127900,0.000000,0.000000,0.000000,0.000000,0.560100,0.000000,0.000000,0.000000,-0.279930,1.000000;;
  }

  Mesh cube3_obj {
   36;
   -0.500000;0.000000;0.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;0.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   -0.500000;0.000000;1.000000;,
   -0.500000;1.000000;1.000000;,
   -0.500000;0.000000;0.000000;,
   -0.500000;1.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;1.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;0.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;0.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   -0.500000;1.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;1.000000;0.000000;,
   0.500000;1.000000;1.000000;,
   0.500000;1.000000;0.000000;,
   -0.500000;0.000000;1.000000;,
   0.500000;0.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;0.000000;1.000000;,
   0.500000;1.000000;1.000000;,
   -0.500000;1.000000;1.000000;;
   12;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;;

   MeshNormals {
    36;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;;
   }

   MeshTextureCoords {
    36;
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    0.000000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    0.000000;-1.000000;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-0.405129;,
    -0.230000;-1.000000;,
    0.000000;-1.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material DefaultLib_Material2 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "taijukei.bmp";
     }
    }
   }
  }
 }
}