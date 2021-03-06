#include "Common.h"

#include "CMDL.h"
#include <rlgl.h>
#include "external/glad.h"
#include "ShaderManager.h"
#include <cstring>

extern Shader shader;
extern Texture2D ColormapTexture;
extern Texture2D PaletteTexture;

Texture2D NormalTexture;

float Normals[][3] = { { -0.525731,  0.000000,  0.850651 },
	{ -0.442863,  0.238856,  0.864188 },
	{ -0.295242,  0.000000,  0.955423 },
	{ -0.309017,  0.500000,  0.809017 },
	{ -0.162460,  0.262866,  0.951056 },
	{  0.000000,  0.000000,  1.000000 },
	{  0.000000,  0.850651,  0.525731 },
	{ -0.147621,  0.716567,  0.681718 },
	{  0.147621,  0.716567,  0.681718 },
	{  0.000000,  0.525731,  0.850651 },
	{  0.309017,  0.500000,  0.809017 },
	{  0.525731,  0.000000,  0.850651 },
	{  0.295242,  0.000000,  0.955423 },
	{  0.442863,  0.238856,  0.864188 },
	{  0.162460,  0.262866,  0.951056 },
	{ -0.681718,  0.147621,  0.716567 },
	{ -0.809017,  0.309017,  0.500000 },
	{ -0.587785,  0.425325,  0.688191 },
	{ -0.850651,  0.525731,  0.000000 },
	{ -0.864188,  0.442863,  0.238856 },
	{ -0.716567,  0.681718,  0.147621 },
	{ -0.688191,  0.587785,  0.425325 },
	{ -0.500000,  0.809017,  0.309017 },
	{ -0.238856,  0.864188,  0.442863 },
	{ -0.425325,  0.688191,  0.587785 },
	{ -0.716567,  0.681718, -0.147621 },
	{ -0.500000,  0.809017, -0.309017 },
	{ -0.525731,  0.850651,  0.000000 },
	{  0.000000,  0.850651, -0.525731 },
	{ -0.238856,  0.864188, -0.442863 },
	{  0.000000,  0.955423, -0.295242 },
	{ -0.262866,  0.951056, -0.162460 },
	{  0.000000,  1.000000,  0.000000 },
	{  0.000000,  0.955423,  0.295242 },
	{ -0.262866,  0.951056,  0.162460 },
	{  0.238856,  0.864188,  0.442863 },
	{  0.262866,  0.951056,  0.162460 },
	{  0.500000,  0.809017,  0.309017 },
	{  0.238856,  0.864188, -0.442863 },
	{  0.262866,  0.951056, -0.162460 },
	{  0.500000,  0.809017, -0.309017 },
	{  0.850651,  0.525731,  0.000000 },
	{  0.716567,  0.681718,  0.147621 },
	{  0.716567,  0.681718, -0.147621 },
	{  0.525731,  0.850651,  0.000000 },
	{  0.425325,  0.688191,  0.587785 },
	{  0.864188,  0.442863,  0.238856 },
	{  0.688191,  0.587785,  0.425325 },
	{  0.809017,  0.309017,  0.500000 },
	{  0.681718,  0.147621,  0.716567 },
	{  0.587785,  0.425325,  0.688191 },
	{  0.955423,  0.295242,  0.000000 },
	{  1.000000,  0.000000,  0.000000 },
	{  0.951056,  0.162460,  0.262866 },
	{  0.850651, -0.525731,  0.000000 },
	{  0.955423, -0.295242,  0.000000 },
	{  0.864188, -0.442863,  0.238856 },
	{  0.951056, -0.162460,  0.262866 },
	{  0.809017, -0.309017,  0.500000 },
	{  0.681718, -0.147621,  0.716567 },
	{  0.850651,  0.000000,  0.525731 },
	{  0.864188,  0.442863, -0.238856 },
	{  0.809017,  0.309017, -0.500000 },
	{  0.951056,  0.162460, -0.262866 },
	{  0.525731,  0.000000, -0.850651 },
	{  0.681718,  0.147621, -0.716567 },
	{  0.681718, -0.147621, -0.716567 },
	{  0.850651,  0.000000, -0.525731 },
	{  0.809017, -0.309017, -0.500000 },
	{  0.864188, -0.442863, -0.238856 },
	{  0.951056, -0.162460, -0.262866 },
	{  0.147621,  0.716567, -0.681718 },
	{  0.309017,  0.500000, -0.809017 },
	{  0.425325,  0.688191, -0.587785 },
	{  0.442863,  0.238856, -0.864188 },
	{  0.587785,  0.425325, -0.688191 },
	{  0.688191,  0.587785, -0.425325 },
	{ -0.147621,  0.716567, -0.681718 },
	{ -0.309017,  0.500000, -0.809017 },
	{  0.000000,  0.525731, -0.850651 },
	{ -0.525731,  0.000000, -0.850651 },
	{ -0.442863,  0.238856, -0.864188 },
	{ -0.295242,  0.000000, -0.955423 },
	{ -0.162460,  0.262866, -0.951056 },
	{  0.000000,  0.000000, -1.000000 },
	{  0.295242,  0.000000, -0.955423 },
	{  0.162460,  0.262866, -0.951056 },
	{ -0.442863, -0.238856, -0.864188 },
	{ -0.309017, -0.500000, -0.809017 },
	{ -0.162460, -0.262866, -0.951056 },
	{  0.000000, -0.850651, -0.525731 },
	{ -0.147621, -0.716567, -0.681718 },
	{  0.147621, -0.716567, -0.681718 },
	{  0.000000, -0.525731, -0.850651 },
	{  0.309017, -0.500000, -0.809017 },
	{  0.442863, -0.238856, -0.864188 },
	{  0.162460, -0.262866, -0.951056 },
	{  0.238856, -0.864188, -0.442863 },
	{  0.500000, -0.809017, -0.309017 },
	{  0.425325, -0.688191, -0.587785 },
	{  0.716567, -0.681718, -0.147621 },
	{  0.688191, -0.587785, -0.425325 },
	{  0.587785, -0.425325, -0.688191 },
	{  0.000000, -0.955423, -0.295242 },
	{  0.000000, -1.000000,  0.000000 },
	{  0.262866, -0.951056, -0.162460 },
	{  0.000000, -0.850651,  0.525731 },
	{  0.000000, -0.955423,  0.295242 },
	{  0.238856, -0.864188,  0.442863 },
	{  0.262866, -0.951056,  0.162460 },
	{  0.500000, -0.809017,  0.309017 },
	{  0.716567, -0.681718,  0.147621 },
	{  0.525731, -0.850651,  0.000000 },
	{ -0.238856, -0.864188, -0.442863 },
	{ -0.500000, -0.809017, -0.309017 },
	{ -0.262866, -0.951056, -0.162460 },
	{ -0.850651, -0.525731,  0.000000 },
	{ -0.716567, -0.681718, -0.147621 },
	{ -0.716567, -0.681718,  0.147621 },
	{ -0.525731, -0.850651,  0.000000 },
	{ -0.500000, -0.809017,  0.309017 },
	{ -0.238856, -0.864188,  0.442863 },
	{ -0.262866, -0.951056,  0.162460 },
	{ -0.864188, -0.442863,  0.238856 },
	{ -0.809017, -0.309017,  0.500000 },
	{ -0.688191, -0.587785,  0.425325 },
	{ -0.681718, -0.147621,  0.716567 },
	{ -0.442863, -0.238856,  0.864188 },
	{ -0.587785, -0.425325,  0.688191 },
	{ -0.309017, -0.500000,  0.809017 },
	{ -0.147621, -0.716567,  0.681718 },
	{ -0.425325, -0.688191,  0.587785 },
	{ -0.162460, -0.262866,  0.951056 },
	{  0.442863, -0.238856,  0.864188 },
	{  0.162460, -0.262866,  0.951056 },
	{  0.309017, -0.500000,  0.809017 },
	{  0.147621, -0.716567,  0.681718 },
	{  0.000000, -0.525731,  0.850651 },
	{  0.425325, -0.688191,  0.587785 },
	{  0.587785, -0.425325,  0.688191 },
	{  0.688191, -0.587785,  0.425325 },
	{ -0.955423,  0.295242,  0.000000 },
	{ -0.951056,  0.162460,  0.262866 },
	{ -1.000000,  0.000000,  0.000000 },
	{ -0.850651,  0.000000,  0.525731 },
	{ -0.955423, -0.295242,  0.000000 },
	{ -0.951056, -0.162460,  0.262866 },
	{ -0.864188,  0.442863, -0.238856 },
	{ -0.951056,  0.162460, -0.262866 },
	{ -0.809017,  0.309017, -0.500000 },
	{ -0.864188, -0.442863, -0.238856 },
	{ -0.951056, -0.162460, -0.262866 },
	{ -0.809017, -0.309017, -0.500000 },
	{ -0.681718,  0.147621, -0.716567 },
	{ -0.681718, -0.147621, -0.716567 },
	{ -0.850651,  0.000000, -0.525731 },
	{ -0.688191,  0.587785, -0.425325 },
	{ -0.587785,  0.425325, -0.688191 },
	{ -0.425325,  0.688191, -0.587785 },
	{ -0.425325, -0.688191, -0.587785 },
	{ -0.587785, -0.425325, -0.688191 },
	{ -0.688191, -0.587785, -0.425325 },
};

/*
CMDL::CMDL(std::string Path)
{
}*/

void CMDL::Init(std::string Path)
{
	this->Path = Path;
}

CMDL::CMDL(std::string Path)
{
	_isValid = false;
	HasRaylibMesh = false;
	CurrentFrame = 0;
	RModel = { 0 };
	RMesh = { 0 };
	RMaterial = { 0 };
	TextureCount = 0;
	_images = nullptr;
	_textures = nullptr;
	Skins = nullptr;
	TexCoords = nullptr;
	Triangles = nullptr;
	Vertices = nullptr;
	Frames = nullptr;
	memset(&MDLHeaderUnion, 0, sizeof(MDLHeaderUnion));
	this->Path = Path;
}

CMDL::~CMDL()
{
	CleanupModel();
}

void CMDL::Setup()
{
	float *normaltextureData = new float[256 * 3];
	memset(normaltextureData, 0, 256 * 3);
	for (uint32_t i = 0; i < 256; i++)
	{
		if (i < 162)
		{
			normaltextureData[(i * 3)] = Normals[i][0];
			normaltextureData[(i * 3) + 1] = Normals[i][1];
			normaltextureData[(i * 3) + 2] = Normals[i][2];
		}
		else
		{
			normaltextureData[(i * 3)] = 0.0f;
			normaltextureData[(i * 3) + 1] = 0.0f;
			normaltextureData[(i * 3) + 2] = 1.0f;
		}
	}

	Image NormalImage = { 0 };
	NormalImage.format = PIXELFORMAT_UNCOMPRESSED_R32G32B32;
	NormalImage.width = 256;
	NormalImage.height = 1;
	NormalImage.mipmaps = 1;
	NormalImage.data = normaltextureData;

	NormalTexture = LoadTextureFromImage(NormalImage);
	SetTextureFilter(NormalTexture, TEXTURE_FILTER_POINT);
	SetTextureWrap(NormalTexture, TEXTURE_WRAP_CLAMP);

	delete[] normaltextureData;
}

std::string TrimAnimName(std::string inAnim)
{
	for (size_t i = 0; i < inAnim.size(); i++)
	{
		if (inAnim[i] >= '0' && inAnim[i] <= '9')
		{
			inAnim[i] = '\0';
		}
	}

	return inAnim;
}

void CMDL::RefreshModel()
{
	CleanupModel();
	_isValid = false;
	size_t bytesRead = 0;
	FILE* f = fopen(Path.c_str(), "rb");

	if (!f)
	{
		Com_Error(ERR_DIALOG, "Failed to load model %s", Path.c_str());
		return;
	}
#if defined(_MSC_VER)
#define CheckBytes(MsgIfFail, Val, ...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u bytes, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead, __VA_ARGS__ ); \
			return;						\
		}								\
	}

#define CheckElems(MsgIfFail, Val, ...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u elements, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead, __VA_ARGS__ ); \
			return;						\
		}								\
	}
#elif defined(__GNUC__)
#define CheckBytes(MsgIfFail, Val, args...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u bytes, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead, args ); \
			return;						\
		}								\
	}

#define CheckElems(MsgIfFail, Val, args...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u elements, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead, args ); \
			return;						\
		}								\
	}
#else

#if __cplusplus >= 202002L

#define CheckBytes(MsgIfFail, Val, ...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u bytes, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead __VA_OPT__(,) __VA_ARGS__ ); \
			return;						\
		}								\
	}

#define CheckElems(MsgIfFail, Val, ...)		\
	{									\
		if(bytesRead < Val)				\
		{								\
			Com_Error(ERR_DIALOG, "Expected %u elements, got %u.\nThe model might be corrupted!\n\n" MsgIfFail, Val, bytesRead __VA_OPT__(,) __VA_ARGS__ ); \
			return;						\
		}								\
	}

#else 

#error "No __VA_ARGS__ support for when no variadic arguments are specified!"

#endif

#endif

	//FMDLHeader header;

	//bytesRead = fread(&header, 1, sizeof(FMDLHeader), f);

	//if (bytesRead < sizeof(FMDLHeader))
	//{
		//Com_Error(ERR_DIALOG, "Failed loading model file! Is it corrupted? (%s)", Path.c_str());
		//return;
	//}

	FMDLInfo mdlInfo;

	bytesRead = fread(&mdlInfo, 1, sizeof(FMDLInfo), f);

	CheckBytes("Failed to load model info!", sizeof(FMDLInfo), 0);

	switch (mdlInfo.Magic)
	{
		// id Poly Model, as seen in Quake 1
	case Int32Magic("IDPO"):
		MDLFormat = EMDLFormat::idPolyModel;
		if (mdlInfo.Version != 6)
		{
			Com_Error(ERR_DIALOG, "Incorrect version for IDPO model! (%s)\nExpected 6, got %u", mdlInfo.Version);
			return;
		}

		// Go back to the beginning and read the header into the union
		fseek(f, 0, 0);
		bytesRead = fread(&MDLHeaderUnion, 1, sizeof(FMDLHeader_IDPO), f);

		CheckBytes("Failed loading the header!", sizeof(FMDLHeader_IDPO), 0);

		break;

		// Raven Poly Model, as seen in Hexen 2
	case Int32Magic("RAPO"):
		MDLFormat = EMDLFormat::RavenPolyModel;
		if (mdlInfo.Version != 50)
		{
			Com_Error(ERR_DIALOG, "Incorrect version for RAPO model! (%s)\nExpected 50, got %u", mdlInfo.Version);
			return;
		}

		// Go back to the beginning and read the header into the union
		fseek(f, 0, 0);
		bytesRead = fread(&MDLHeaderUnion, 1, sizeof(FMDLHeader_RAPO), f);

		CheckBytes("Failed loading the header!", sizeof(FMDLHeader_RAPO), 0);

		break;
	}

	// Skin time

	Skins = Com_Calloc(FMDLSkinBase *, MDLHeader.NumSkins);

	TextureCount = 0;

	for (uint32_t i = 0; i < MDLHeader.NumSkins; i++)
	{
		uint32_t group = -1;

		bytesRead = fread(&group, 1, sizeof(FMDLSkinBase), f);

		CheckBytes("Failed loading group number for skin %d!", sizeof(FMDLSkinBase), i);

		Skins[i] = 0;

		// Single
		if (group == 0)
		{
			FMDLSkin* skin = Com_Calloc(FMDLSkin, 1);

			skin->Group = 0;

			skin->Data = new uint8_t[GetSkinByteLength()];

			bytesRead = fread(skin->Data, 1, GetSkinByteLength(), f);
			CheckBytes("Failed reading texture data for skin %d!", GetSkinByteLength(), i);

			Skins[i] = skin;

			TextureCount++;
		}
		// Group (animated texture)
		else if (group == 1)
		{
			Com_Error(ERR_DIALOG, "Support for animated textures is not implemented yet!", i);
			return;
		}
		else
		{
			Com_Error(ERR_DIALOG, "Invalid group for skin %d!", i);
			return;
		}
	}

	// Texture coordinate time
	if (MDLFormat == EMDLFormat::idPolyModel)
	{
		TexCoords = Com_Calloc(FMDLTexCoord, MDLHeader.NumVerts);
		bytesRead = fread(TexCoords, sizeof(FMDLTexCoord), MDLHeader.NumVerts, f);
		CheckElems("Failed reading texture coordinates!", MDLHeader.NumVerts, 0);
	}
	else if (MDLFormat == EMDLFormat::RavenPolyModel)
	{
		TexCoords = Com_Calloc(FMDLTexCoord, GetMDLHeader<FMDLHeader_RAPO>().NumTexCoords);
		bytesRead = fread(TexCoords, sizeof(FMDLTexCoord), GetMDLHeader<FMDLHeader_RAPO>().NumTexCoords, f);
		CheckElems("Failed reading texture coordinates!", GetMDLHeader<FMDLHeader_RAPO>().NumTexCoords, 0);
	}
	else
	{
		Com_Error(ERR_DIALOG, "Could not load texture coordinates! Invalid MDL format!");
		return;
	}

	Triangles = Com_Calloc(FMDLTriangle, MDLHeader.NumTris); // new FMDLTriangle[MDLHeader.NumTris];
	bytesRead = fread(Triangles, sizeof(FMDLTriangle), MDLHeader.NumTris, f);
	CheckElems("Failed reading triangles!", MDLHeader.NumTris, 0);

	// Very naive code assuming we have only a single simple frame
#if 0
	//fseek(f, 4*6, 1);
	fseek(f, 4, 1);
	fseek(f, sizeof(FMDLVertex), 1);
	fseek(f, sizeof(FMDLVertex), 1);
	fseek(f, 16, 1);

	Vertices = new FMDLVertex[MDLHeader.NumVerts];
	bytesRead = fread(Vertices, sizeof(FMDLVertex), MDLHeader.NumVerts, f);
	CheckElems("Failed reading vertices!", MDLHeader.NumVerts);
#endif

	//Frames = new FMDLFrameBase * [MDLHeader.NumFrames];
	Frames = Com_Calloc(FMDLFrameBase *, MDLHeader.NumFrames);
	FMDLAnimation AllAnim;
	strcpy(AllAnim.Name, "All");
	AllAnim.Begin = 0;
	FMDLAnimation CurrentAnim;
	bool FoundAnim = false;
	AnimPoses = 0;

	for (uint32_t i = 0; i < MDLHeader.NumFrames; i++)
	{
		int type = 0;
		bytesRead = fread(&type, 1, sizeof(int), f);
		CheckBytes("Failed checking the type for frame %u", sizeof(int), i);

		Frames[i] = nullptr;

		if (type == 0)
		{
			FMDLSimpleFrame* CurrentFrame = Com_Calloc(FMDLSimpleFrame, 1);// new FMDLSimpleFrame();
			CurrentFrame->Type = 0;
			
			// lets read both at once, why not!
			bytesRead = fread(&CurrentFrame->BBoxMin, 1, sizeof(FMDLVertex) * 2, f);
			CheckBytes("Failed reading the bounding box for frame %u (type = simple)", sizeof(FMDLVertex) * 2, i);

			bytesRead = fread(&CurrentFrame->Name, 1, 16, f);
			CheckBytes("Failed reading name for frame %u (type = simple)", 16, i);

			CurrentFrame->Vertex = Com_Calloc(FMDLVertex, MDLHeader.NumVerts);//new FMDLVertex[MDLHeader.NumVerts];
			bytesRead = fread(CurrentFrame->Vertex, sizeof(FMDLVertex), MDLHeader.NumVerts, f);
			CheckElems("Failed reading vertices for frame %u (type = simple)", MDLHeader.NumVerts, i);

			
			std::string trimmedName = TrimAnimName(CurrentFrame->Name);

			if (strcmp(CurrentAnim.Name, trimmedName.c_str()) != 0)
			{
				if (FoundAnim)
				{
					AnimationSets.push_back(CurrentAnim);
				}
				strcpy(CurrentAnim.Name, trimmedName.c_str());
				CurrentAnim.Begin = AnimPoses;
				FoundAnim = true;
			}
			CurrentAnim.End = AnimPoses;

			// Fill up the vertex buffer for posterity, but technically we dont need it
			if (AnimPoses == 0)
			{
				Vertices = Com_Calloc(FMDLVertex, MDLHeader.NumVerts);//new FMDLVertex[MDLHeader.NumVerts];
				memcpy(Vertices, CurrentFrame->Vertex, sizeof(FMDLVertex)*MDLHeader.NumVerts);
			}

			AnimPoseToFrameMap[AnimPoses] = i;

			Frames[i] = CurrentFrame;
			AnimPoses++;
		}
		else
		{
			FMDLGroupFrame* CurrentFrame = Com_Calloc(FMDLGroupFrame, 1);
			CurrentFrame->Type = 1;

			bytesRead = fread(&CurrentFrame->NumFrames, 1, sizeof(int32_t), f);
			CheckBytes("Failed reading the frame count for frame %u (type = group)", sizeof(int32_t), i);

			// lets read both at once, why not!
			bytesRead = fread(&CurrentFrame->BBoxMin, 1, sizeof(FMDLVertex) * 2, f);
			CheckBytes("Failed reading the bounding box for frame %u (type = group)", sizeof(FMDLVertex) * 2, i);

			CurrentFrame->Time = Com_Calloc(float, CurrentFrame->NumFrames);

			bytesRead = fread(CurrentFrame->Time, 1, CurrentFrame->NumFrames * sizeof(float), f);
			CheckBytes("Failed reading the time intervals for frame %u (type = group)", CurrentFrame->NumFrames * sizeof(float), i);

			CurrentFrame->Frames = Com_Calloc(FMDLSimpleFrame*, CurrentFrame->NumFrames);

			CurrentFrame->PoseBegin = AnimPoses;

			for (int16_t o = 0; o < CurrentFrame->NumFrames; o++)
			{
				CurrentFrame->Frames[o] = Com_Calloc(FMDLSimpleFrame, MDLHeader.NumVerts);

				// i just found out group frames are just multiple simple frames
				// this sucks man

				bytesRead = fread(&CurrentFrame->Frames[o]->BBoxMin, 1, sizeof(FMDLVertex) * 2, f);
				CheckBytes("Failed reading the bounding box for frame %u:%d", sizeof(FMDLVertex) * 2, i, o);

				bytesRead = fread(&CurrentFrame->Frames[o]->Name, 1, 16, f);
				CheckBytes("Failed reading name for frame %u:%d", 16, i, o);

				std::string trimmedName = std::string(TextFormat("Group%03d_", i)) + TrimAnimName(CurrentFrame->Frames[o]->Name);

				if (strcmp(CurrentAnim.Name, trimmedName.c_str()) != 0)
				{
					if (FoundAnim)
					{
						AnimationSets.push_back(CurrentAnim);
					}
					strcpy(CurrentAnim.Name, trimmedName.c_str());
					CurrentAnim.Begin = AnimPoses;
					FoundAnim = true;
				}
				CurrentAnim.End = AnimPoses;

				CurrentFrame->Frames[o]->Vertex = Com_Calloc(FMDLVertex, MDLHeader.NumVerts);

				bytesRead = fread(CurrentFrame->Frames[o]->Vertex, sizeof(FMDLVertex), MDLHeader.NumVerts, f);
				CheckElems("Failed reading the vertex data for frame %u:%u (type = group)", MDLHeader.NumVerts, i, o);

				if (AnimPoses == 0)
				{
					Vertices = Com_Calloc(FMDLVertex, MDLHeader.NumVerts);
					memcpy(Vertices, CurrentFrame->Frames[o], sizeof(FMDLVertex) * MDLHeader.NumVerts);
				}

				AnimPoseToFrameMap[AnimPoses] = i;

				AnimPoses++;
			}

			Frames[i] = CurrentFrame;
		}
	}

	AnimationSets.push_back(CurrentAnim);
	AllAnim.End = AnimPoses;
	AnimationSets.emplace(AnimationSets.begin(), AllAnim);

	fclose(f);


#undef CheckBytes
#undef CheckElems
	_isValid = true;

	UpdateModel();
}

void CMDL::UpdateModel()
{
	HasRaylibMesh = false;

	_images = Com_Calloc(Image, TextureCount);//new Image[TextureCount];
	_textures = Com_Calloc(Texture2D, TextureCount);//new Texture2D[TextureCount];
	uint32_t imgIndex = 0;
	for (uint32_t i = 0; i < MDLHeader.NumSkins; i++)
	{
		if (Skins[i]->Group == 0)
		{
			_images[imgIndex].width = MDLHeader.SkinWidth;
			_images[imgIndex].height = MDLHeader.SkinHeight;
			_images[imgIndex].mipmaps = 1;
			_images[imgIndex].format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
			_images[imgIndex].data = ((FMDLSkin*)Skins[i])->Data;

			_textures[imgIndex] = LoadTextureFromImage(_images[i]);

			imgIndex++;
		}
		else
		{
			Com_Error(ERR_FATAL, "Animated textures are not supported yet!");
		}
	}

	memset(&RMesh, 0, sizeof(RMesh));
	RMesh = { 0 };

	//Mesh.vertexCount = Mesh.triangleCount * 3 * 3;// MDLHeader.NumVerts;
	RMesh.triangleCount = MDLHeader.NumTris;
	RMesh.vertexCount = RMesh.triangleCount * 3;

	RMesh.vertices = Com_Calloc(float, RMesh.triangleCount * 3 * 3);
	RMesh.normals = Com_Calloc(float, RMesh.triangleCount * 3 * 3);
	RMesh.texcoords = Com_Calloc(float, RMesh.triangleCount * 3 * 2);
	RMesh.tangents = Com_Calloc(float, RMesh.triangleCount * 3 * 4);
	//Mesh.indices = new uint16_t[Mesh.triangleCount * 3];
	//Mesh.colors = new uint8_t[Mesh.triangleCount * 3 * 4];

	/*
	for (uint32_t v = 0; v < Mesh.vertexCount; v++)
	{
		Vector3 Transformed = GetTransformedVertexPosition(Vertices[v].Position);
		Mesh.vertices[(v * 3)] = Transformed.x;
		Mesh.vertices[(v * 3) + 1] = Transformed.y;
		Mesh.vertices[(v * 3) + 2] = Transformed.z;
	}

	for (uint32_t v = 0; v < Mesh.vertexCount; v++)
	{
		Vector2 UV = GetUV(TexCoords[v]);
		Mesh.texcoords[(v * 2)] = UV.x;
		Mesh.texcoords[(v * 2) + 1] = UV.y;
	}

	for (uint32_t v = 0; v < Mesh.vertexCount; v++)
	{
		Vector2 UV = GetUV(TexCoords[v]);
		Mesh.colors[(v * 4)] = (UV.x * 255);
		Mesh.colors[(v * 4) + 1] = (UV.y * 255);
		Mesh.colors[(v * 4) + 2] = 255;
		Mesh.colors[(v * 4) + 3] = 255;
	}

	for (uint32_t v = 0; v < Mesh.triangleCount; v++)
	{
		Mesh.indices[(v * 3)] = Triangles[v].Vertex[0];
		Mesh.indices[(v * 3)+2] = Triangles[v].Vertex[1];
		Mesh.indices[(v * 3)+1] = Triangles[v].Vertex[2];
	}*/

	for (uint32_t v = 0; v < RMesh.triangleCount; v++)
	{
		for (uint32_t c = 0; c < 3; c++)
		{
			uint32_t tv = c;
			//if (c == 1) tv = 2;
			//if (c == 2) tv = 1;
			uint32_t vertID;
			FMDLVertex* vert;
			Vector2 UV = { 0 };
			switch (MDLFormat)
			{
			case EMDLFormat::idPolyModel:
				vertID = Triangles[v].Vertex[tv];
				vert = &Vertices[vertID];
				UV = GetUV(TexCoords[vertID], Triangles[v]);
				break;
			case EMDLFormat::RavenPolyModel:
				vertID = Triangles[v].RAPOTri.Vertex[tv];
				uint32_t tcID = Triangles[v].RAPOTri.ST[tv];
				vert = &Vertices[vertID];
				UV = GetUV(TexCoords[tcID], Triangles[v]);
				break;
			}
			RMesh.texcoords[(v * 3 * 2) + (c*2)] = UV.x;
			RMesh.texcoords[(v * 3 * 2) + (c*2) + 1] = UV.y;
			/*
			Mesh.colors[(v * 3 * 4) + (c * 4)] = (UV.x * 255);
			Mesh.colors[(v * 3 * 4) + (c * 4) + 1] = (UV.y * 255);
			Mesh.colors[(v * 3 * 4) + (c * 4) + 2] = 255;
			Mesh.colors[(v * 3 * 4) + (c * 4) + 3] = 255;
			*/

			// Converting to Y-up

			RMesh.normals[(v * 3 * 3) + (c * 3)] = Normals[vert->NormalIndex][0];
			RMesh.normals[(v * 3 * 3) + (c * 3) + 1] = Normals[vert->NormalIndex][2];
			RMesh.normals[(v * 3 * 3) + (c * 3) + 2] = -Normals[vert->NormalIndex][1];
			
			Vector3 Transformed = GetTransformedVertexPosition(vert->Position);
			
			RMesh.vertices[(v * 3 * 3) + (c * 3)] = MDLHeader.Translate[0] ;// Transformed.x;
			RMesh.vertices[(v * 3 * 3) + (c * 3) + 1] = MDLHeader.Translate[1];//Transformed.z;
			RMesh.vertices[(v * 3 * 3) + (c * 3) + 2] = MDLHeader.Translate[2];// -Transformed.y;
			
			/*
			Mesh.vertices[(v * 3 * 3) + (c * 3)] =  Transformed.x;
			Mesh.vertices[(v * 3 * 3) + (c * 3) + 1] = Transformed.z;
			Mesh.vertices[(v * 3 * 3) + (c * 3) + 2] = -Transformed.y;
			*/
			// this is a tangent buffer, i know, but ill use it for vertex animation and no one is gonna stop me
			// +0.1f actually makes it work. dont ask me how
			RMesh.tangents[(v * 3 * 4) + (c*4)] = (((float)vertID+0.1f) / (float)MDLHeader.NumVerts);
		}
	}

	Image VertexAnim = { 0 };
	VertexAnim.width = MDLHeader.NumVerts;
	VertexAnim.height = AnimPoses; // TODO: Add more frames
	VertexAnim.mipmaps = 1;
	VertexAnim.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8; // 8-bits per component
	uint8_t *vertexAnimData = Com_Calloc(uint8_t, MDLHeader.NumVerts * AnimPoses * 4);
	int32_t CurrentPose = 0;

	for (uint32_t f = 0; f < MDLHeader.NumFrames; f++)
	{
		int Type = Frames[f]->Type;
		if (Type == 0)
		{
			for (uint32_t v = 0; v < MDLHeader.NumVerts; v++)
			{
				FMDLVertex* vert = &((FMDLSimpleFrame*)Frames[f])->Vertex[v];

				vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4)] = vert->Position[0];
				vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 1] = vert->Position[1];
				vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 2] = vert->Position[2];
				vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 3] = vert->NormalIndex + (0.1f / 256.f);
			}
			CurrentPose++;
		}
		else
		{
			FMDLGroupFrame* gf = (FMDLGroupFrame*)Frames[f];
			for (uint32_t g = 0; g < gf->NumFrames; g++)
			{
				// Dummy data for now
				for (uint32_t v = 0; v < MDLHeader.NumVerts; v++)
				{
					FMDLVertex* vert = &(gf->Frames[g]->Vertex[v]);

					vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4)] = vert->Position[0];
					vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 1] = vert->Position[1];
					vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 2] = vert->Position[2];
					vertexAnimData[(CurrentPose * MDLHeader.NumVerts * 4) + (v * 4) + 3] = vert->NormalIndex + (0.1f / 256.f);
				}
				CurrentPose++;
			}
		}
	}

	VertexAnim.data = vertexAnimData;

	SimpleFrameTexture = LoadTextureFromImage(VertexAnim);
	SetTextureFilter(SimpleFrameTexture, TEXTURE_FILTER_POINT);
	SetTextureWrap(SimpleFrameTexture, TEXTURE_WRAP_CLAMP);

	//delete[] (vertexAnimData);
	Com_Free(vertexAnimData);

	UploadMesh(&RMesh, false);
	
	RModel = LoadModelFromMesh(RMesh);

	RMaterial = LoadMaterialDefault();

	RMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _textures[0];
	RMaterial.maps[1].texture = ColormapTexture;
	RMaterial.maps[2].texture = PaletteTexture;
	RMaterial.maps[3].texture = SimpleFrameTexture;
	RMaterial.maps[4].texture = NormalTexture;

	ChangeRenderMode(RENDERMODE_DEFAULT, UseAnimInterpolation);

	AnimData.TargetFrame = 1;
	AnimData.FrameCount = AnimPoses;
	AnimData.Interpolate = 0;

	GViewerSettings.AnimBegin = 0;
	GViewerSettings.AnimEnd = AnimPoses - 1;
	GViewerSettings.CurrentAnimIndex = 0;

	GViewerSettings.FloorOffset = MDLHeader.Translate[2];
	
	HasRaylibMesh = true;
}

void CMDL::CleanupModel()
{
	HasRaylibMesh = false;
	_isValid = false;
	// Clean up raylib model data
	for (uint32_t i = 0; i < TextureCount; i++)
	{
		if (_textures)
		{
			UnloadTexture(_textures[i]);
		}
		if (_images)
		{
			UnloadImage(_images[i]);
		}
	}
	Com_Free(_images);
	Com_Free(_textures);

	Com_Free(RMesh.vertices);
	Com_Free(RMesh.normals);
	Com_Free(RMesh.texcoords);
	Com_Free(RMesh.tangents);

	UnloadShader(RShader);
	// Clean up original model data
	if (Skins)
	{
		for (uint32_t i = 0; i < MDLHeader.NumSkins; i++)
		{
			if (Skins[i])
			{
				Com_Free(Skins[i]);
			}
		}
	}
	Com_Free(Skins);
	Com_Free(TexCoords);
	Com_Free(Triangles);
	if (Frames)
	{
		for (uint32_t i = 0; i < MDLHeader.NumFrames; i++)
		{
			if (Frames[i])
			{
				if (Frames[i]->Type == 0)
				{
					FMDLSimpleFrame* frame = (FMDLSimpleFrame*)Frames[i];
					Com_Free(frame->Vertex);
				}
				else
				{
					FMDLGroupFrame* frame = (FMDLGroupFrame*)Frames[i];

					Com_Free(frame->Time);

					for (uint32_t g = 0; g < frame->NumFrames; g++)
					{
						Com_Free(frame->Frames[g]->Vertex);
						Com_Free(frame->Frames[g]);
					}
					Com_Free(frame->Frames);
				}
				Com_Free(Frames[i]);
			}
		}
	}
	Com_Free(Frames);
	Com_Free(Vertices);

	AnimationSets.clear();
	AnimPoseToFrameMap.clear();
	TextureCount = 0;
}

void CMDL::DrawModel()
{
	SetShaderValue(RShader, GetShaderLocation(RShader, "animData"), &AnimData, SHADER_UNIFORM_IVEC4);

	return;
}

void CMDL::Frame(float delta, uint32_t begin, uint32_t end)
{
	// 10 FPS by default
	float frameTime = 1.f / 10.f;
	uint32_t CurrentFrameIndex = AnimPoseToFrameMap[AnimData.CurrentFrame];
	uint32_t TargetFrameIndex = AnimPoseToFrameMap[AnimData.TargetFrame];
	
	if (CurrentFrameIndex == TargetFrameIndex)
	{
		// Check if we're in a group frame
		if (Frames[CurrentFrameIndex]->Type == 1)
		{
			FMDLGroupFrame* gf = (FMDLGroupFrame*)Frames[CurrentFrameIndex];
			// We're in a group frame, modify the interval
			uint32_t gfc = AnimData.CurrentFrame - gf->PoseBegin;
			uint32_t gft = AnimData.TargetFrame - gf->PoseBegin;

			float tt = gf->Time[gft];
			float tc = gf->Time[gfc];

			frameTime = tt - (gft > gfc ? tc : 0.0f);
		}
	}

	float currentInterp = AnimData.GetInterpolate();

	currentInterp += delta / frameTime;

	if (currentInterp > 1.0f)
	{
		currentInterp = fmod(currentInterp, 1.0f);

		AnimData.CurrentFrame = AnimData.TargetFrame;

		if (++AnimData.TargetFrame > end || AnimData.TargetFrame < begin)
		{
			AnimData.TargetFrame = begin;
		}
	}
	AnimData.SetInterpolate(currentInterp);
}

void CMDL::ChangeRenderMode(uint32_t renderMode, bool useAnimInterpolation, bool Force)
{
	if (Force || (renderMode != CurrentRenderMode || useAnimInterpolation != UseAnimInterpolation))
	{
		CurrentRenderMode = (LunarRenderMode)renderMode;
		UseAnimInterpolation = useAnimInterpolation;
		UnloadShader(RShader);

		RShader = LoadShader(ShaderManager::GetVertexShaderPath("model_quake1_mdl", renderMode, UseAnimInterpolation), ShaderManager::GetFragmentShaderPath("model_quake1_mdl", renderMode, UseAnimInterpolation));
		RShader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(RShader, "matModel");
		RShader.locs[SHADER_LOC_MATRIX_NORMAL] = GetShaderLocation(RShader, "matNormal");
		RShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(RShader, "viewPos");
		RShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(RShader, "textureModelSkin");
		RShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(RShader, "textureColormapLUT");
		RShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(RShader, "texturePaletteLUT");
		RShader.locs[SHADER_LOC_MAP_ROUGHNESS] = GetShaderLocation(RShader, "textureVertexAnim");
		RShader.locs[SHADER_LOC_MAP_OCCLUSION] = GetShaderLocation(RShader, "textureNormalLUT");

		SetShaderValue(RShader, GetShaderLocation(RShader, "modelScale"), &MDLHeader.Scale[0], SHADER_UNIFORM_VEC3);

		RMaterial.shader = RShader;
		RMaterial.maps[1].texture = ColormapTexture;
		RMaterial.maps[2].texture = PaletteTexture;
		RMaterial.maps[3].texture = SimpleFrameTexture;
		RMaterial.maps[4].texture = NormalTexture;
	}
}
