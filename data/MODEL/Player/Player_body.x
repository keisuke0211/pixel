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
 300;
 -7.00000;2.00000;-0.00000;,
 -7.00000;0.00000;-1.00000;,
 -7.00000;0.00000;2.00000;,
 -7.00000;2.00000;1.00000;,
 -7.00000;3.00000;-0.00000;,
 -7.00000;3.00000;-0.00000;,
 -7.00000;2.00000;-0.00000;,
 -7.00000;2.00000;1.00000;,
 -7.00000;3.00000;1.00000;,
 -7.00000;3.00000;1.00000;,
 -7.00000;4.00000;-1.00000;,
 -7.00000;4.00000;2.00000;,
 -6.00000;2.00000;-5.00000;,
 -6.00000;0.00000;-5.00000;,
 -6.00000;0.00000;-1.00000;,
 -6.00000;2.00000;-1.00000;,
 -6.00000;2.00000;2.00000;,
 -6.00000;0.00000;2.00000;,
 -6.00000;0.00000;5.00000;,
 -6.00000;2.00000;5.00000;,
 -6.00000;4.00000;-5.00000;,
 -6.00000;2.00000;-5.00000;,
 -6.00000;2.00000;-1.00000;,
 -6.00000;4.00000;-1.00000;,
 -6.00000;4.00000;2.00000;,
 -6.00000;2.00000;2.00000;,
 -6.00000;2.00000;5.00000;,
 -6.00000;4.00000;5.00000;,
 -6.00000;13.00000;-1.00000;,
 -6.00000;12.00000;-1.00000;,
 -6.00000;12.00000;2.00000;,
 -6.00000;13.00000;2.00000;,
 -5.00000;8.00000;-3.00000;,
 -5.00000;4.00000;-3.00000;,
 -5.00000;4.00000;4.00000;,
 -5.00000;8.00000;4.00000;,
 -5.00000;12.00000;-1.00000;,
 -5.00000;10.00000;-1.00000;,
 -5.00000;10.00000;2.00000;,
 -5.00000;12.00000;2.00000;,
 -4.00000;8.00000;-4.00000;,
 -4.00000;4.00000;-4.00000;,
 -4.00000;4.00000;-3.00000;,
 -4.00000;8.00000;-3.00000;,
 -4.00000;10.00000;-4.00000;,
 -4.00000;8.00000;-4.00000;,
 -4.00000;8.00000;-3.00000;,
 -4.00000;8.00000;3.00000;,
 -4.00000;10.00000;-3.00000;,
 -4.00000;10.00000;-1.00000;,
 -4.00000;10.00000;2.00000;,
 -4.00000;11.00000;-3.00000;,
 -4.00000;11.00000;-1.00000;,
 -4.00000;11.00000;2.00000;,
 -4.00000;11.00000;3.00000;,
 -4.00000;12.00000;-3.00000;,
 -4.00000;11.00000;-3.00000;,
 -4.00000;11.00000;-1.00000;,
 -4.00000;12.00000;-1.00000;,
 -4.00000;13.00000;-3.00000;,
 -4.00000;12.00000;-3.00000;,
 -4.00000;12.00000;-1.00000;,
 -4.00000;13.00000;-1.00000;,
 -3.00000;11.00000;-4.00000;,
 -3.00000;10.00000;-4.00000;,
 -3.00000;10.00000;-3.00000;,
 -3.00000;11.00000;-3.00000;,
 -2.00000;12.00000;-4.00000;,
 -2.00000;11.00000;-4.00000;,
 -2.00000;11.00000;-3.00000;,
 -2.00000;12.00000;-3.00000;,
 2.00000;11.00000;-4.00000;,
 2.00000;12.00000;-4.00000;,
 2.00000;11.00000;-3.00000;,
 2.00000;12.00000;-3.00000;,
 3.00000;10.00000;-4.00000;,
 3.00000;11.00000;-4.00000;,
 3.00000;10.00000;-3.00000;,
 3.00000;11.00000;-3.00000;,
 4.00000;4.00000;-4.00000;,
 4.00000;8.00000;-4.00000;,
 4.00000;4.00000;-3.00000;,
 4.00000;8.00000;-3.00000;,
 4.00000;8.00000;-4.00000;,
 4.00000;10.00000;-4.00000;,
 4.00000;8.00000;-3.00000;,
 4.00000;8.00000;3.00000;,
 4.00000;10.00000;-3.00000;,
 4.00000;10.00000;-1.00000;,
 4.00000;10.00000;2.00000;,
 4.00000;11.00000;-3.00000;,
 4.00000;11.00000;-1.00000;,
 4.00000;11.00000;2.00000;,
 4.00000;11.00000;3.00000;,
 4.00000;11.00000;-3.00000;,
 4.00000;12.00000;-3.00000;,
 4.00000;11.00000;-1.00000;,
 4.00000;12.00000;-1.00000;,
 4.00000;12.00000;-3.00000;,
 4.00000;13.00000;-3.00000;,
 4.00000;12.00000;-1.00000;,
 4.00000;13.00000;-1.00000;,
 5.00000;4.00000;-3.00000;,
 5.00000;8.00000;-3.00000;,
 5.00000;4.00000;4.00000;,
 5.00000;8.00000;4.00000;,
 5.00000;10.00000;-1.00000;,
 5.00000;12.00000;-1.00000;,
 5.00000;10.00000;2.00000;,
 5.00000;12.00000;2.00000;,
 6.00000;0.00000;-5.00000;,
 6.00000;2.00000;-5.00000;,
 6.00000;0.00000;-1.00000;,
 6.00000;2.00000;-1.00000;,
 6.00000;0.00000;2.00000;,
 6.00000;2.00000;2.00000;,
 6.00000;0.00000;5.00000;,
 6.00000;2.00000;5.00000;,
 6.00000;2.00000;-5.00000;,
 6.00000;4.00000;-5.00000;,
 6.00000;2.00000;-1.00000;,
 6.00000;4.00000;-1.00000;,
 6.00000;2.00000;2.00000;,
 6.00000;4.00000;2.00000;,
 6.00000;2.00000;5.00000;,
 6.00000;4.00000;5.00000;,
 6.00000;12.00000;-1.00000;,
 6.00000;13.00000;-1.00000;,
 6.00000;12.00000;2.00000;,
 6.00000;13.00000;2.00000;,
 7.00000;0.00000;-1.00000;,
 7.00000;2.00000;-0.00000;,
 7.00000;0.00000;2.00000;,
 7.00000;2.00000;1.00000;,
 7.00000;3.00000;-0.00000;,
 7.00000;2.00000;-0.00000;,
 7.00000;3.00000;-0.00000;,
 7.00000;2.00000;1.00000;,
 7.00000;3.00000;1.00000;,
 7.00000;3.00000;1.00000;,
 7.00000;4.00000;-1.00000;,
 7.00000;4.00000;2.00000;,
 -3.00000;2.00000;-5.00000;,
 -3.00000;2.00000;-5.00000;,
 -3.00000;4.00000;-5.00000;,
 -2.00000;0.00000;-5.00000;,
 -2.00000;2.00000;-5.00000;,
 -3.00000;2.00000;-5.00000;,
 -3.00000;4.00000;-5.00000;,
 -2.00000;2.00000;-5.00000;,
 -2.00000;4.00000;-5.00000;,
 -1.00000;0.00000;-5.00000;,
 -2.00000;0.00000;-5.00000;,
 -2.00000;2.00000;-5.00000;,
 -1.00000;2.00000;-5.00000;,
 -2.00000;2.00000;-5.00000;,
 -2.00000;4.00000;-5.00000;,
 -1.00000;2.00000;-5.00000;,
 -1.00000;3.00000;-5.00000;,
 0.00000;3.00000;-5.00000;,
 -1.00000;2.00000;-5.00000;,
 -1.00000;3.00000;-5.00000;,
 0.00000;3.00000;-5.00000;,
 0.00000;4.00000;-5.00000;,
 1.00000;0.00000;-5.00000;,
 -1.00000;0.00000;-5.00000;,
 -1.00000;2.00000;-5.00000;,
 1.00000;2.00000;-5.00000;,
 1.00000;2.00000;-5.00000;,
 0.00000;4.00000;-5.00000;,
 1.00000;4.00000;-5.00000;,
 2.00000;0.00000;-5.00000;,
 1.00000;0.00000;-5.00000;,
 1.00000;2.00000;-5.00000;,
 2.00000;2.00000;-5.00000;,
 1.00000;2.00000;-5.00000;,
 1.00000;4.00000;-5.00000;,
 2.00000;2.00000;-5.00000;,
 2.00000;4.00000;-5.00000;,
 3.00000;2.00000;-5.00000;,
 2.00000;0.00000;-5.00000;,
 2.00000;2.00000;-5.00000;,
 3.00000;2.00000;-5.00000;,
 2.00000;2.00000;-5.00000;,
 2.00000;4.00000;-5.00000;,
 3.00000;4.00000;-5.00000;,
 3.00000;2.00000;-5.00000;,
 3.00000;4.00000;-5.00000;,
 -3.00000;4.00000;-4.00000;,
 -3.00000;8.00000;-4.00000;,
 -3.00000;8.00000;-4.00000;,
 -3.00000;9.00000;-4.00000;,
 -3.00000;10.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -3.00000;9.00000;-4.00000;,
 -2.00000;9.00000;-4.00000;,
 -2.00000;9.00000;-4.00000;,
 -3.00000;9.00000;-4.00000;,
 -2.00000;11.00000;-4.00000;,
 -1.00000;4.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -2.00000;9.00000;-4.00000;,
 -1.00000;9.00000;-4.00000;,
 -2.00000;9.00000;-4.00000;,
 -2.00000;11.00000;-4.00000;,
 -1.00000;9.00000;-4.00000;,
 -1.00000;11.00000;-4.00000;,
 -1.00000;11.00000;-4.00000;,
 -1.00000;12.00000;-4.00000;,
 0.00000;4.00000;-4.00000;,
 -1.00000;4.00000;-4.00000;,
 -1.00000;9.00000;-4.00000;,
 1.00000;4.00000;-4.00000;,
 1.00000;9.00000;-4.00000;,
 1.00000;9.00000;-4.00000;,
 1.00000;11.00000;-4.00000;,
 -1.00000;11.00000;-4.00000;,
 -1.00000;12.00000;-4.00000;,
 1.00000;11.00000;-4.00000;,
 1.00000;12.00000;-4.00000;,
 2.00000;4.00000;-4.00000;,
 1.00000;4.00000;-4.00000;,
 1.00000;9.00000;-4.00000;,
 2.00000;9.00000;-4.00000;,
 2.00000;9.00000;-4.00000;,
 1.00000;11.00000;-4.00000;,
 1.00000;12.00000;-4.00000;,
 2.00000;11.00000;-4.00000;,
 3.00000;4.00000;-4.00000;,
 2.00000;4.00000;-4.00000;,
 2.00000;9.00000;-4.00000;,
 3.00000;8.00000;-4.00000;,
 3.00000;9.00000;-4.00000;,
 2.00000;9.00000;-4.00000;,
 2.00000;11.00000;-4.00000;,
 3.00000;9.00000;-4.00000;,
 3.00000;8.00000;-4.00000;,
 3.00000;9.00000;-4.00000;,
 3.00000;10.00000;-4.00000;,
 -3.00000;10.00000;-3.00000;,
 -3.00000;11.00000;-3.00000;,
 -3.00000;12.00000;-3.00000;,
 -3.00000;12.00000;-3.00000;,
 -2.00000;11.00000;-3.00000;,
 -2.00000;12.00000;-3.00000;,
 -1.00000;12.00000;-3.00000;,
 1.00000;12.00000;-3.00000;,
 2.00000;12.00000;-3.00000;,
 3.00000;11.00000;-3.00000;,
 2.00000;11.00000;-3.00000;,
 3.00000;12.00000;-3.00000;,
 3.00000;10.00000;-3.00000;,
 3.00000;12.00000;-3.00000;,
 -6.00000;0.00000;-1.00000;,
 6.00000;0.00000;-1.00000;,
 -6.00000;0.00000;2.00000;,
 -4.00000;12.00000;2.00000;,
 -4.00000;11.00000;2.00000;,
 4.00000;11.00000;2.00000;,
 -4.00000;12.00000;2.00000;,
 4.00000;12.00000;2.00000;,
 4.00000;12.00000;2.00000;,
 6.00000;0.00000;2.00000;,
 -2.00000;0.00000;-4.00000;,
 -2.00000;0.00000;-4.00000;,
 -1.00000;0.00000;-4.00000;,
 -1.00000;0.00000;-4.00000;,
 1.00000;0.00000;-4.00000;,
 1.00000;0.00000;-4.00000;,
 2.00000;0.00000;-4.00000;,
 2.00000;0.00000;-4.00000;,
 -4.00000;4.00000;-4.00000;,
 -3.00000;4.00000;-4.00000;,
 -3.00000;4.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -2.00000;4.00000;-4.00000;,
 -1.00000;4.00000;-4.00000;,
 0.00000;4.00000;-4.00000;,
 0.00000;4.00000;-4.00000;,
 1.00000;4.00000;-4.00000;,
 1.00000;4.00000;-4.00000;,
 2.00000;4.00000;-4.00000;,
 2.00000;4.00000;-4.00000;,
 3.00000;4.00000;-4.00000;,
 3.00000;4.00000;-4.00000;,
 4.00000;4.00000;-4.00000;,
 -5.00000;4.00000;-3.00000;,
 -4.00000;4.00000;-3.00000;,
 4.00000;4.00000;-3.00000;,
 5.00000;4.00000;-3.00000;,
 -5.00000;4.00000;4.00000;,
 5.00000;4.00000;4.00000;,
 -4.00000;8.00000;3.00000;,
 4.00000;8.00000;3.00000;,
 -2.00000;11.00000;-3.00000;,
 2.00000;11.00000;-3.00000;,
 -1.00000;12.00000;-3.00000;,
 -1.00000;12.00000;-3.00000;,
 1.00000;12.00000;-3.00000;,
 1.00000;12.00000;-3.00000;;
 
 318;
 3;0,1,2;,
 3;3,0,2;,
 3;4,1,0;,
 3;5,6,7;,
 3;8,3,2;,
 3;9,5,7;,
 3;10,1,4;,
 3;10,4,8;,
 3;11,8,2;,
 3;11,10,8;,
 3;12,13,14;,
 3;15,12,14;,
 3;16,17,18;,
 3;19,16,18;,
 3;20,21,22;,
 3;23,20,22;,
 3;24,25,26;,
 3;27,24,26;,
 3;28,29,30;,
 3;31,28,30;,
 3;32,33,34;,
 3;35,32,34;,
 3;36,37,38;,
 3;39,36,38;,
 3;40,41,42;,
 3;43,40,42;,
 3;44,45,46;,
 3;44,46,47;,
 3;48,44,47;,
 3;49,48,47;,
 3;50,49,47;,
 3;51,48,49;,
 3;52,51,49;,
 3;53,50,47;,
 3;54,53,47;,
 3;55,56,57;,
 3;58,55,57;,
 3;59,60,61;,
 3;62,59,61;,
 3;63,64,65;,
 3;66,63,65;,
 3;67,68,69;,
 3;70,67,69;,
 3;71,72,73;,
 3;72,74,73;,
 3;75,76,77;,
 3;76,78,77;,
 3;79,80,81;,
 3;80,82,81;,
 3;83,84,85;,
 3;85,84,86;,
 3;84,87,86;,
 3;87,88,86;,
 3;88,89,86;,
 3;87,90,88;,
 3;90,91,88;,
 3;89,92,86;,
 3;92,93,86;,
 3;94,95,96;,
 3;95,97,96;,
 3;98,99,100;,
 3;99,101,100;,
 3;102,103,104;,
 3;103,105,104;,
 3;106,107,108;,
 3;107,109,108;,
 3;110,111,112;,
 3;111,113,112;,
 3;114,115,116;,
 3;115,117,116;,
 3;118,119,120;,
 3;119,121,120;,
 3;122,123,124;,
 3;123,125,124;,
 3;126,127,128;,
 3;127,129,128;,
 3;130,131,132;,
 3;131,133,132;,
 3;130,134,131;,
 3;135,136,137;,
 3;133,138,132;,
 3;136,139,137;,
 3;130,140,134;,
 3;134,140,138;,
 3;138,141,132;,
 3;140,141,138;,
 3;142,13,12;,
 3;143,21,20;,
 3;144,143,20;,
 3;145,13,142;,
 3;146,147,148;,
 3;149,145,142;,
 3;150,146,148;,
 3;151,152,153;,
 3;154,155,156;,
 3;157,151,153;,
 3;158,154,156;,
 3;159,160,161;,
 3;162,158,156;,
 3;163,162,156;,
 3;164,165,166;,
 3;167,160,159;,
 3;168,164,166;,
 3;167,159,169;,
 3;170,167,169;,
 3;171,172,173;,
 3;174,175,176;,
 3;177,171,173;,
 3;178,174,176;,
 3;179,180,181;,
 3;182,183,184;,
 3;185,182,184;,
 3;110,180,179;,
 3;118,186,187;,
 3;111,110,179;,
 3;119,118,187;,
 3;188,41,40;,
 3;189,45,44;,
 3;190,188,40;,
 3;191,189,44;,
 3;192,191,44;,
 3;193,188,190;,
 3;193,190,194;,
 3;195,64,63;,
 3;196,193,194;,
 3;195,197,64;,
 3;198,195,63;,
 3;199,200,201;,
 3;202,203,204;,
 3;205,199,201;,
 3;206,68,67;,
 3;207,202,204;,
 3;208,206,67;,
 3;209,210,211;,
 3;212,209,211;,
 3;213,202,207;,
 3;214,212,211;,
 3;215,216,217;,
 3;218,213,207;,
 3;219,215,217;,
 3;220,221,222;,
 3;223,213,218;,
 3;224,220,222;,
 3;71,225,226;,
 3;227,223,218;,
 3;72,71,226;,
 3;228,229,230;,
 3;231,228,230;,
 3;232,233,234;,
 3;235,231,230;,
 3;75,232,234;,
 3;76,75,234;,
 3;79,228,231;,
 3;83,236,237;,
 3;80,79,231;,
 3;83,237,238;,
 3;84,83,238;,
 3;42,33,32;,
 3;43,42,32;,
 3;239,48,51;,
 3;66,56,55;,
 3;240,239,51;,
 3;241,60,59;,
 3;242,66,55;,
 3;243,240,241;,
 3;244,241,59;,
 3;244,243,241;,
 3;245,244,59;,
 3;246,245,59;,
 3;247,246,59;,
 3;248,249,247;,
 3;250,247,59;,
 3;250,248,247;,
 3;87,251,248;,
 3;94,78,252;,
 3;90,87,248;,
 3;98,250,59;,
 3;95,94,252;,
 3;99,98,59;,
 3;102,81,82;,
 3;103,102,82;,
 3;253,1,10;,
 3;22,253,10;,
 3;23,22,10;,
 3;36,29,28;,
 3;49,37,36;,
 3;52,49,36;,
 3;61,36,28;,
 3;61,52,36;,
 3;62,61,28;,
 3;106,88,91;,
 3;106,100,101;,
 3;106,91,100;,
 3;107,106,101;,
 3;126,107,101;,
 3;127,126,101;,
 3;130,120,121;,
 3;130,254,120;,
 3;140,130,121;,
 3;2,255,11;,
 3;255,25,11;,
 3;25,24,11;,
 3;30,39,31;,
 3;38,50,39;,
 3;50,53,39;,
 3;39,256,31;,
 3;53,256,39;,
 3;257,258,259;,
 3;256,260,31;,
 3;258,261,259;,
 3;89,108,92;,
 3;92,108,260;,
 3;260,109,31;,
 3;108,109,260;,
 3;109,128,31;,
 3;128,129,31;,
 3;122,132,123;,
 3;262,132,122;,
 3;132,141,123;,
 3;47,86,54;,
 3;86,93,54;,
 3;34,104,35;,
 3;104,105,35;,
 3;18,116,19;,
 3;26,124,27;,
 3;116,117,19;,
 3;124,125,27;,
 3;263,13,145;,
 3;264,152,151;,
 3;265,165,164;,
 3;266,264,151;,
 3;267,172,171;,
 3;268,265,164;,
 3;269,180,110;,
 3;270,267,171;,
 3;14,265,268;,
 3;14,263,265;,
 3;14,268,269;,
 3;14,13,263;,
 3;112,269,110;,
 3;112,14,269;,
 3;2,1,253;,
 3;17,14,112;,
 3;255,2,253;,
 3;262,254,130;,
 3;114,17,112;,
 3;132,262,130;,
 3;18,17,114;,
 3;116,18,114;,
 3;38,37,49;,
 3;50,38,49;,
 3;89,88,106;,
 3;108,89,106;,
 3;30,29,36;,
 3;39,30,36;,
 3;109,107,126;,
 3;128,109,126;,
 3;20,271,144;,
 3;148,272,150;,
 3;271,273,144;,
 3;156,274,163;,
 3;272,275,150;,
 3;274,276,163;,
 3;169,277,170;,
 3;276,278,163;,
 3;176,279,178;,
 3;277,280,170;,
 3;184,281,185;,
 3;279,282,178;,
 3;187,283,119;,
 3;281,284,185;,
 3;283,285,119;,
 3;20,286,271;,
 3;286,287,271;,
 3;285,288,119;,
 3;288,289,119;,
 3;20,23,286;,
 3;289,121,119;,
 3;10,11,23;,
 3;23,24,286;,
 3;11,24,23;,
 3;121,123,140;,
 3;289,123,121;,
 3;123,141,140;,
 3;24,290,286;,
 3;289,291,123;,
 3;24,27,290;,
 3;290,27,291;,
 3;291,125,123;,
 3;27,125,291;,
 3;32,292,43;,
 3;82,293,103;,
 3;32,35,292;,
 3;292,35,293;,
 3;293,105,103;,
 3;35,105,293;,
 3;44,48,192;,
 3;48,239,192;,
 3;238,251,84;,
 3;251,87,84;,
 3;63,66,198;,
 3;66,294,198;,
 3;234,295,76;,
 3;295,78,76;,
 3;53,54,92;,
 3;54,93,92;,
 3;67,70,208;,
 3;217,296,219;,
 3;70,297,208;,
 3;226,298,72;,
 3;296,299,219;,
 3;298,74,72;,
 3;59,62,99;,
 3;62,101,99;,
 3;28,31,62;,
 3;101,31,127;,
 3;62,31,101;,
 3;31,129,127;;
 
 MeshMaterialList {
  1;
  318;
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
    "data\\TEXTURE\\Player.png";
   }
  }
 }
 MeshNormals {
  10;
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  318;
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
  3;0,1,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,0,0;,
  3;0,1,0;,
  3;1,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,1,0;,
  3;1,0,0;,
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
  3;1,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,3,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,2,2;,
  3;2,3,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,3,2;,
  3;3,2,2;,
  3;2,3,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,7,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,9,8;;
 }
 MeshTextureCoords {
  300;
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
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
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
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
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
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
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
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
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.798828;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.798828;0.500000;,
  0.021484;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.369141;0.500000;,
  0.798828;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.369141;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.728516;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.798828;0.500000;,
  0.728516;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.798828;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.537109;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.021484;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.021484;0.500000;,
  0.369141;0.500000;,
  0.537109;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.369141;0.500000;,
  0.728516;0.500000;,
  0.728516;0.500000;,
  0.537109;0.500000;,
  0.537109;0.500000;,
  0.728516;0.500000;,
  0.798828;0.500000;,
  0.798828;0.500000;,
  0.728516;0.500000;;
 }
}
