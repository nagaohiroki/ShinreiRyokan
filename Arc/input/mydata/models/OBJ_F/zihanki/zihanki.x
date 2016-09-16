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
 

 Frame zihanki {
  

  FrameTransformMatrix {
   0.489111,0.000000,0.000000,0.000000,0.000000,0.786211,0.000000,0.000000,0.000000,0.000000,0.228150,0.000000,0.500000,0.000000,0.000000,1.000000;;
  }

  Mesh zihanki_obj {
   36;
   -2.000000;0.000000;-2.000000;,
   -2.000000;2.000000;-2.000000;,
   0.000000;2.000000;-2.000000;,
   -2.000000;0.000000;-2.000000;,
   0.000000;2.000000;-2.000000;,
   0.000000;0.000000;-2.000000;,
   -2.000000;0.000000;-2.000000;,
   0.000000;0.000000;-2.000000;,
   0.000000;0.000000;0.000000;,
   -2.000000;0.000000;-2.000000;,
   0.000000;0.000000;0.000000;,
   -2.000000;0.000000;0.000000;,
   -2.000000;0.000000;-2.000000;,
   -2.000000;0.000000;0.000000;,
   -2.000000;2.000000;0.000000;,
   -2.000000;0.000000;-2.000000;,
   -2.000000;2.000000;0.000000;,
   -2.000000;2.000000;-2.000000;,
   0.000000;0.000000;-2.000000;,
   0.000000;2.000000;-2.000000;,
   0.000000;2.000000;0.000000;,
   0.000000;0.000000;-2.000000;,
   0.000000;2.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   -2.000000;2.000000;-2.000000;,
   -2.000000;2.000000;0.000000;,
   0.000000;2.000000;0.000000;,
   -2.000000;2.000000;-2.000000;,
   0.000000;2.000000;0.000000;,
   0.000000;2.000000;-2.000000;,
   -2.000000;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   0.000000;2.000000;0.000000;,
   -2.000000;0.000000;0.000000;,
   0.000000;2.000000;0.000000;,
   -2.000000;2.000000;0.000000;;
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
    -0.171729;0.002072;,
    -0.171729;-0.997928;,
    0.001334;-0.994983;,
    -0.171729;0.002072;,
    0.001334;-0.994983;,
    0.001334;0.005017;,
    -0.005004;-0.090467;,
    -0.167820;-0.090467;,
    -0.167820;-0.388552;,
    -0.005004;-0.090467;,
    -0.167820;-0.388552;,
    -0.005004;-0.388552;,
    -0.002344;0.002442;,
    -0.169409;0.002442;,
    -0.169409;-0.997558;,
    -0.002344;0.002442;,
    -0.169409;-0.997558;,
    -0.002344;-0.997558;,
    -0.994833;0.007050;,
    -0.994833;-0.992950;,
    -0.828730;-0.992950;,
    -0.994833;0.007050;,
    -0.828730;-0.992950;,
    -0.828730;0.007050;,
    -0.004394;-0.390728;,
    -0.004394;-0.093878;,
    -0.170483;-0.093878;,
    -0.004394;-0.390728;,
    -0.170483;-0.093878;,
    -0.170483;-0.390728;,
    -0.168618;0.005274;,
    -0.827503;0.004578;,
    -0.827503;-0.995422;,
    -0.168618;0.005274;,
    -0.827503;-0.995422;,
    -0.168618;-0.994726;;
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

    Material DefaultLib_Material33 {
     0.700000;0.700000;0.700000;1.000000;;
     50.000000;
     1.000000;1.000000;1.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "zihanki.bmp";
     }
    }
   }
  }
 }
}