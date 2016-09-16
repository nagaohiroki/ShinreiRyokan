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
 

 Frame cylinder1 {
  

  FrameTransformMatrix {
   0.853112,0.000000,0.000000,0.000000,0.000000,0.379376,0.000000,0.000000,0.000000,0.000000,1.133883,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh cylinder1_obj {
   60;
   -0.070711;0.000000;0.070711;,
   -0.080698;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   -0.080698;0.000000;0.000000;,
   -0.070711;0.000000;0.070711;,
   -0.070711;0.500000;0.070711;,
   -0.080698;0.000000;0.000000;,
   -0.070711;0.500000;0.070711;,
   -0.080698;0.500000;0.000000;,
   -0.080698;0.500000;0.000000;,
   -0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.100000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.000000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.000000;0.500000;0.100000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.500000;0.100000;,
   -0.070711;0.500000;0.070711;,
   -0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.100000;,
   0.000000;0.500000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.000000;0.100000;,
   0.070711;0.000000;0.070711;,
   0.070711;0.500000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.100000;,
   0.000000;0.500000;0.100000;,
   0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.000000;,
   0.077481;0.000000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.077481;0.000000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.077481;0.500000;0.000000;,
   0.070711;0.500000;0.070711;,
   0.070711;0.500000;0.070711;,
   0.077481;0.500000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.077481;0.000000;0.000000;,
   -0.080698;0.000000;0.000000;,
   -0.080698;0.500000;0.000000;,
   0.000000;0.500000;0.000000;,
   -0.080698;0.000000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.000000;;
   20;
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
   3;57,58,59;;

   MeshNormals {
    60;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.990172;0.000000;0.139858;,
    -0.790478;0.000000;0.612491;,
    -0.790478;0.000000;0.612491;,
    -0.990172;0.000000;0.139858;,
    -0.790478;0.000000;0.612491;,
    -0.990172;0.000000;0.139858;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;0.000000;1.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.382683;0.000000;0.923880;,
    0.382683;0.000000;0.923880;,
    0.000000;0.000000;1.000000;,
    0.382683;0.000000;0.923880;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;;
    20;
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
    3;57,58,59;;
   }

   MeshTextureCoords {
    60;
    -0.076374;-0.312837;,
    -0.030389;-0.090805;,
    -0.187390;-0.090805;,
    -0.030389;-0.090805;,
    -0.252422;-0.090805;,
    -0.252422;-0.404806;,
    -0.030389;-0.090805;,
    -0.252422;-0.404806;,
    -0.030389;-0.404806;,
    -0.346801;-0.947797;,
    -0.364340;-0.863111;,
    -0.406684;-0.947797;,
    -0.187390;-0.404806;,
    -0.076374;-0.312837;,
    -0.187390;-0.090805;,
    -0.076374;-0.090805;,
    -0.187390;-0.090805;,
    -0.187390;-0.404806;,
    -0.076374;-0.090805;,
    -0.187390;-0.404806;,
    -0.076374;-0.404806;,
    -0.364340;-0.863111;,
    -0.406684;-0.828032;,
    -0.406684;-0.947797;,
    -0.298406;-0.312837;,
    -0.187390;-0.404806;,
    -0.187390;-0.090805;,
    -0.187390;-0.090805;,
    -0.298406;-0.090805;,
    -0.298406;-0.404806;,
    -0.187390;-0.090805;,
    -0.298406;-0.404806;,
    -0.187390;-0.404806;,
    -0.406684;-0.828032;,
    -0.449027;-0.863111;,
    -0.406684;-0.947797;,
    -0.344391;-0.090805;,
    -0.298406;-0.312837;,
    -0.187390;-0.090805;,
    -0.122358;-0.090805;,
    -0.344391;-0.090805;,
    -0.344391;-0.404806;,
    -0.122358;-0.090805;,
    -0.344391;-0.404806;,
    -0.122358;-0.404806;,
    -0.449027;-0.863111;,
    -0.466566;-0.947797;,
    -0.406684;-0.947797;,
    -0.187390;-0.090805;,
    -0.187390;-0.404806;,
    -0.030389;-0.404806;,
    -0.187390;-0.090805;,
    -0.030389;-0.404806;,
    -0.030389;-0.090805;,
    -0.344391;-0.090805;,
    -0.344391;-0.404806;,
    -0.187390;-0.404806;,
    -0.344391;-0.090805;,
    -0.187390;-0.404806;,
    -0.187390;-0.090805;;
   }

   MeshMaterialList {
    1;
    20;
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

    Material DefaultLib_Material59 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "toile.bmp";
     }
    }
   }
  }
 }

 Frame cylinder2 {
  

  FrameTransformMatrix {
   -0.853112,-0.000000,0.000000,0.000000,0.000000,-0.104647,0.000000,0.000000,0.000000,0.000000,1.133883,0.000000,0.000000,0.243966,0.000000,1.000000;;
  }

  Mesh cylinder2_obj {
   60;
   -0.070711;0.000000;0.070711;,
   -0.080698;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   -0.080698;0.000000;0.000000;,
   -0.070711;0.000000;0.070711;,
   -0.070711;0.500000;0.070711;,
   -0.080698;0.000000;0.000000;,
   -0.070711;0.500000;0.070711;,
   -0.080698;0.500000;0.000000;,
   -0.080698;0.500000;0.000000;,
   -0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.100000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.000000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.000000;0.500000;0.100000;,
   -0.070711;0.000000;0.070711;,
   0.000000;0.500000;0.100000;,
   -0.070711;0.500000;0.070711;,
   -0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.100000;,
   0.000000;0.500000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.000000;0.100000;,
   0.070711;0.000000;0.070711;,
   0.070711;0.500000;0.070711;,
   0.000000;0.000000;0.100000;,
   0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.100000;,
   0.000000;0.500000;0.100000;,
   0.070711;0.500000;0.070711;,
   0.000000;0.500000;0.000000;,
   0.077481;0.000000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.000000;0.000000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.077481;0.000000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.070711;0.000000;0.070711;,
   0.077481;0.500000;0.000000;,
   0.070711;0.500000;0.070711;,
   0.070711;0.500000;0.070711;,
   0.077481;0.500000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.077481;0.500000;0.000000;,
   0.077481;0.000000;0.000000;,
   -0.080698;0.000000;0.000000;,
   -0.080698;0.500000;0.000000;,
   0.000000;0.500000;0.000000;,
   -0.080698;0.000000;0.000000;,
   0.000000;0.500000;0.000000;,
   0.000000;0.000000;0.000000;;
   20;
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
   3;57,58,59;;

   MeshNormals {
    60;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.990172;0.000000;0.139858;,
    -0.790478;0.000000;0.612491;,
    -0.790478;0.000000;0.612491;,
    -0.990172;0.000000;0.139858;,
    -0.790478;0.000000;0.612491;,
    -0.990172;0.000000;0.139858;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;0.000000;1.000000;,
    -0.790478;0.000000;0.612491;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.382683;0.000000;0.923880;,
    0.382683;0.000000;0.923880;,
    0.000000;0.000000;1.000000;,
    0.382683;0.000000;0.923880;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.995447;0.000000;0.095316;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;;
    20;
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
    3;57,58,59;;
   }

   MeshTextureCoords {
    60;
    -0.076374;-0.312837;,
    -0.030389;-0.090805;,
    -0.187390;-0.090805;,
    -0.030389;-0.090805;,
    -0.252422;-0.090805;,
    -0.252422;-0.404806;,
    -0.030389;-0.090805;,
    -0.252422;-0.404806;,
    -0.030389;-0.404806;,
    -0.346801;-0.947797;,
    -0.364340;-0.863111;,
    -0.406684;-0.947797;,
    -0.187390;-0.404806;,
    -0.076374;-0.312837;,
    -0.187390;-0.090805;,
    -0.076374;-0.090805;,
    -0.187390;-0.090805;,
    -0.187390;-0.404806;,
    -0.076374;-0.090805;,
    -0.187390;-0.404806;,
    -0.076374;-0.404806;,
    -0.364340;-0.863111;,
    -0.406684;-0.828032;,
    -0.406684;-0.947797;,
    -0.298406;-0.312837;,
    -0.187390;-0.404806;,
    -0.187390;-0.090805;,
    -0.187390;-0.090805;,
    -0.298406;-0.090805;,
    -0.298406;-0.404806;,
    -0.187390;-0.090805;,
    -0.298406;-0.404806;,
    -0.187390;-0.404806;,
    -0.406684;-0.828032;,
    -0.449027;-0.863111;,
    -0.406684;-0.947797;,
    -0.344391;-0.090805;,
    -0.298406;-0.312837;,
    -0.187390;-0.090805;,
    -0.122358;-0.090805;,
    -0.344391;-0.090805;,
    -0.344391;-0.404806;,
    -0.122358;-0.090805;,
    -0.344391;-0.404806;,
    -0.122358;-0.404806;,
    -0.449027;-0.863111;,
    -0.466566;-0.947797;,
    -0.406684;-0.947797;,
    -0.187390;-0.090805;,
    -0.187390;-0.404806;,
    -0.030389;-0.404806;,
    -0.187390;-0.090805;,
    -0.030389;-0.404806;,
    -0.030389;-0.090805;,
    -0.344391;-0.090805;,
    -0.344391;-0.404806;,
    -0.187390;-0.404806;,
    -0.344391;-0.090805;,
    -0.187390;-0.404806;,
    -0.187390;-0.090805;;
   }

   MeshMaterialList {
    1;
    20;
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

    Material DefaultLib_Material59 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "toile.bmp";
     }
    }
   }
  }
 }
}