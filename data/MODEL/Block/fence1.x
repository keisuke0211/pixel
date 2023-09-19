xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 104;
 -2.50000;20.00000;-20.00000;,
 2.50000;-20.00000;-20.00000;,
 -2.50000;-20.00000;-20.00000;,
 2.50000;20.00000;-20.00000;,
 -2.50000;-10.00000;-10.00000;,
 2.50000;-20.00000;-10.00000;,
 -2.50000;-20.00000;-10.00000;,
 2.50000;-10.00000;-10.00000;,
 -2.50000;7.50000;-10.00000;,
 2.50000;-5.00000;-10.00000;,
 -2.50000;-5.00000;-10.00000;,
 2.50000;7.50000;-10.00000;,
 -2.50000;17.50000;-10.00000;,
 2.50000;12.50000;-10.00000;,
 -2.50000;12.50000;-10.00000;,
 2.50000;17.50000;-10.00000;,
 -2.50000;20.00000;-7.50000;,
 2.50000;17.50000;-7.50000;,
 -2.50000;17.50000;-7.50000;,
 2.50000;20.00000;-7.50000;,
 -2.50000;-10.00000;2.50000;,
 2.50000;-20.00000;2.50000;,
 -2.50000;-20.00000;2.50000;,
 2.50000;-10.00000;2.50000;,
 -2.50000;7.50000;2.50000;,
 2.50000;-5.00000;2.50000;,
 -2.50000;-5.00000;2.50000;,
 2.50000;7.50000;2.50000;,
 -2.50000;17.50000;2.50000;,
 2.50000;12.50000;2.50000;,
 -2.50000;12.50000;2.50000;,
 2.50000;17.50000;2.50000;,
 -2.50000;20.00000;5.00000;,
 2.50000;17.50000;5.00000;,
 -2.50000;17.50000;5.00000;,
 2.50000;20.00000;5.00000;,
 -2.50000;-10.00000;15.00000;,
 2.50000;-20.00000;15.00000;,
 -2.50000;-20.00000;15.00000;,
 2.50000;-10.00000;15.00000;,
 -2.50000;7.50000;15.00000;,
 2.50000;-5.00000;15.00000;,
 -2.50000;-5.00000;15.00000;,
 2.50000;7.50000;15.00000;,
 -2.50000;17.50000;15.00000;,
 2.50000;12.50000;15.00000;,
 -2.50000;12.50000;15.00000;,
 2.50000;17.50000;15.00000;,
 -2.50000;20.00000;17.50000;,
 2.50000;17.50000;17.50000;,
 -2.50000;17.50000;17.50000;,
 2.50000;20.00000;17.50000;,
 -2.50000;17.50000;-17.50000;,
 2.50000;17.50000;-17.50000;,
 -2.50000;20.00000;-17.50000;,
 2.50000;20.00000;-17.50000;,
 -2.50000;-20.00000;-15.00000;,
 2.50000;-20.00000;-15.00000;,
 -2.50000;-10.00000;-15.00000;,
 2.50000;-10.00000;-15.00000;,
 -2.50000;-5.00000;-15.00000;,
 2.50000;-5.00000;-15.00000;,
 -2.50000;7.50000;-15.00000;,
 2.50000;7.50000;-15.00000;,
 -2.50000;12.50000;-15.00000;,
 2.50000;12.50000;-15.00000;,
 -2.50000;17.50000;-15.00000;,
 2.50000;17.50000;-15.00000;,
 -2.50000;17.50000;-5.00000;,
 2.50000;17.50000;-5.00000;,
 -2.50000;20.00000;-5.00000;,
 2.50000;20.00000;-5.00000;,
 -2.50000;-20.00000;-2.50000;,
 2.50000;-20.00000;-2.50000;,
 -2.50000;-10.00000;-2.50000;,
 2.50000;-10.00000;-2.50000;,
 -2.50000;-5.00000;-2.50000;,
 2.50000;-5.00000;-2.50000;,
 -2.50000;7.50000;-2.50000;,
 2.50000;7.50000;-2.50000;,
 -2.50000;12.50000;-2.50000;,
 2.50000;12.50000;-2.50000;,
 -2.50000;17.50000;-2.50000;,
 2.50000;17.50000;-2.50000;,
 -2.50000;17.50000;7.50000;,
 2.50000;17.50000;7.50000;,
 -2.50000;20.00000;7.50000;,
 2.50000;20.00000;7.50000;,
 -2.50000;-20.00000;10.00000;,
 2.50000;-20.00000;10.00000;,
 -2.50000;-10.00000;10.00000;,
 2.50000;-10.00000;10.00000;,
 -2.50000;-5.00000;10.00000;,
 2.50000;-5.00000;10.00000;,
 -2.50000;7.50000;10.00000;,
 2.50000;7.50000;10.00000;,
 -2.50000;12.50000;10.00000;,
 2.50000;12.50000;10.00000;,
 -2.50000;17.50000;10.00000;,
 2.50000;17.50000;10.00000;,
 -2.50000;-20.00000;20.00000;,
 2.50000;-20.00000;20.00000;,
 -2.50000;20.00000;20.00000;,
 2.50000;20.00000;20.00000;;
 
 216;
 3;0,1,2;,
 3;3,1,0;,
 3;4,5,6;,
 3;7,5,4;,
 3;8,9,10;,
 3;11,9,8;,
 3;12,13,14;,
 3;15,13,12;,
 3;16,17,18;,
 3;19,17,16;,
 3;20,21,22;,
 3;23,21,20;,
 3;24,25,26;,
 3;27,25,24;,
 3;28,29,30;,
 3;31,29,28;,
 3;32,33,34;,
 3;35,33,32;,
 3;36,37,38;,
 3;39,37,36;,
 3;40,41,42;,
 3;43,41,40;,
 3;44,45,46;,
 3;47,45,44;,
 3;48,49,50;,
 3;51,49,48;,
 3;52,53,54;,
 3;54,53,55;,
 3;56,57,58;,
 3;58,57,59;,
 3;60,61,62;,
 3;62,61,63;,
 3;64,65,66;,
 3;66,65,67;,
 3;68,69,70;,
 3;70,69,71;,
 3;72,73,74;,
 3;74,73,75;,
 3;76,77,78;,
 3;78,77,79;,
 3;80,81,82;,
 3;82,81,83;,
 3;84,85,86;,
 3;86,85,87;,
 3;88,89,90;,
 3;90,89,91;,
 3;92,93,94;,
 3;94,93,95;,
 3;96,97,98;,
 3;98,97,99;,
 3;100,101,102;,
 3;102,101,103;,
 3;52,0,2;,
 3;54,0,52;,
 3;56,52,2;,
 3;58,52,56;,
 3;60,52,58;,
 3;62,52,60;,
 3;64,52,62;,
 3;66,52,64;,
 3;4,60,58;,
 3;10,60,4;,
 3;8,64,62;,
 3;14,64,8;,
 3;18,10,4;,
 3;18,12,14;,
 3;18,14,8;,
 3;18,8,10;,
 3;18,4,6;,
 3;68,18,6;,
 3;68,16,18;,
 3;70,16,68;,
 3;72,68,6;,
 3;74,68,72;,
 3;76,68,74;,
 3;78,68,76;,
 3;80,68,78;,
 3;82,68,80;,
 3;20,76,74;,
 3;26,76,20;,
 3;24,80,78;,
 3;30,80,24;,
 3;34,26,20;,
 3;34,28,30;,
 3;34,30,24;,
 3;34,24,26;,
 3;34,20,22;,
 3;84,34,22;,
 3;84,32,34;,
 3;86,32,84;,
 3;88,84,22;,
 3;90,84,88;,
 3;92,84,90;,
 3;94,84,92;,
 3;96,84,94;,
 3;98,84,96;,
 3;36,92,90;,
 3;42,92,36;,
 3;40,96,94;,
 3;46,96,40;,
 3;50,42,36;,
 3;50,44,46;,
 3;50,46,40;,
 3;50,40,42;,
 3;50,36,38;,
 3;100,50,38;,
 3;100,48,50;,
 3;102,48,100;,
 3;1,3,53;,
 3;53,3,55;,
 3;1,53,57;,
 3;57,53,59;,
 3;59,53,61;,
 3;61,53,63;,
 3;63,53,65;,
 3;65,53,67;,
 3;59,61,7;,
 3;7,61,9;,
 3;63,65,11;,
 3;11,65,13;,
 3;7,9,17;,
 3;13,15,17;,
 3;11,13,17;,
 3;9,11,17;,
 3;5,7,17;,
 3;5,17,69;,
 3;17,19,69;,
 3;69,19,71;,
 3;5,69,73;,
 3;73,69,75;,
 3;75,69,77;,
 3;77,69,79;,
 3;79,69,81;,
 3;81,69,83;,
 3;75,77,23;,
 3;23,77,25;,
 3;79,81,27;,
 3;27,81,29;,
 3;23,25,33;,
 3;29,31,33;,
 3;27,29,33;,
 3;25,27,33;,
 3;21,23,33;,
 3;21,33,85;,
 3;33,35,85;,
 3;85,35,87;,
 3;21,85,89;,
 3;89,85,91;,
 3;91,85,93;,
 3;93,85,95;,
 3;95,85,97;,
 3;97,85,99;,
 3;91,93,39;,
 3;39,93,41;,
 3;95,97,43;,
 3;43,97,45;,
 3;39,41,49;,
 3;45,47,49;,
 3;43,45,49;,
 3;41,43,49;,
 3;37,39,49;,
 3;37,49,101;,
 3;49,51,101;,
 3;101,51,103;,
 3;1,56,2;,
 3;57,56,1;,
 3;5,72,6;,
 3;73,72,5;,
 3;21,88,22;,
 3;89,88,21;,
 3;37,100,38;,
 3;101,100,37;,
 3;59,4,58;,
 3;7,4,59;,
 3;75,20,74;,
 3;23,20,75;,
 3;91,36,90;,
 3;39,36,91;,
 3;63,8,62;,
 3;11,8,63;,
 3;79,24,78;,
 3;27,24,79;,
 3;95,40,94;,
 3;43,40,95;,
 3;60,10,61;,
 3;61,10,9;,
 3;76,26,77;,
 3;77,26,25;,
 3;92,42,93;,
 3;93,42,41;,
 3;64,14,65;,
 3;65,14,13;,
 3;80,30,81;,
 3;81,30,29;,
 3;96,46,97;,
 3;97,46,45;,
 3;52,66,53;,
 3;53,66,67;,
 3;12,18,15;,
 3;15,18,17;,
 3;68,82,69;,
 3;69,82,83;,
 3;28,34,31;,
 3;31,34,33;,
 3;84,98,85;,
 3;85,98,99;,
 3;44,50,47;,
 3;47,50,49;,
 3;0,54,3;,
 3;3,54,55;,
 3;16,70,19;,
 3;19,70,71;,
 3;32,86,35;,
 3;35,86,87;,
 3;48,102,51;,
 3;51,102,103;;
 
 MeshMaterialList {
  1;
  216;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\OBJ\\WoodenBox.png";
   }
  }
 }
 MeshNormals {
  59;
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  216;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,3,4;,
  3;3,3,2;,
  3;5,2,4;,
  3;6,2,5;,
  3;7,2,6;,
  3;6,2,7;,
  3;7,2,6;,
  3;8,2,7;,
  3;9,7,6;,
  3;10,7,9;,
  3;9,7,6;,
  3;10,7,9;,
  3;11,10,9;,
  3;11,12,10;,
  3;11,10,9;,
  3;11,9,10;,
  3;11,9,13;,
  3;14,11,13;,
  3;14,8,11;,
  3;8,8,14;,
  3;15,14,13;,
  3;16,14,15;,
  3;17,14,16;,
  3;16,14,17;,
  3;18,14,16;,
  3;19,14,18;,
  3;20,17,16;,
  3;21,17,20;,
  3;18,18,16;,
  3;16,18,18;,
  3;22,21,20;,
  3;22,19,16;,
  3;22,16,18;,
  3;22,18,21;,
  3;22,20,23;,
  3;24,22,23;,
  3;24,8,22;,
  3;8,8,24;,
  3;25,24,23;,
  3;10,24,25;,
  3;9,24,10;,
  3;10,24,9;,
  3;9,24,10;,
  3;12,24,9;,
  3;7,9,10;,
  3;6,9,7;,
  3;7,9,10;,
  3;6,9,7;,
  3;26,6,7;,
  3;26,8,6;,
  3;26,6,7;,
  3;26,7,6;,
  3;26,7,27;,
  3;28,26,27;,
  3;28,3,26;,
  3;3,3,28;,
  3;29,30,31;,
  3;31,30,30;,
  3;29,31,32;,
  3;32,31,33;,
  3;33,31,34;,
  3;34,31,33;,
  3;33,31,34;,
  3;34,31,35;,
  3;33,34,36;,
  3;36,34,37;,
  3;33,34,36;,
  3;36,34,37;,
  3;36,37,38;,
  3;37,39,38;,
  3;36,37,38;,
  3;37,36,38;,
  3;40,36,38;,
  3;40,38,41;,
  3;38,35,41;,
  3;41,35,35;,
  3;40,41,42;,
  3;42,41,43;,
  3;43,41,44;,
  3;44,41,43;,
  3;43,41,45;,
  3;45,41,46;,
  3;43,44,47;,
  3;47,44,48;,
  3;43,45,45;,
  3;45,45,43;,
  3;47,48,49;,
  3;43,46,49;,
  3;45,43,49;,
  3;48,45,49;,
  3;50,47,49;,
  3;50,49,51;,
  3;49,35,51;,
  3;51,35,35;,
  3;50,51,52;,
  3;52,51,37;,
  3;37,51,36;,
  3;36,51,37;,
  3;37,51,36;,
  3;36,51,39;,
  3;37,36,34;,
  3;34,36,33;,
  3;37,36,34;,
  3;34,36,33;,
  3;34,33,53;,
  3;33,35,53;,
  3;34,33,53;,
  3;33,34,53;,
  3;54,34,53;,
  3;54,53,55;,
  3;53,30,55;,
  3;55,30,30;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;56,56,56;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;58,57,57;,
  3;57,57,58;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;58,57,57;,
  3;57,57,58;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;;
 }
 MeshTextureCoords {
  104;
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;;
 }
}