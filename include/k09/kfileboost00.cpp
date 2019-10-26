
/*
	kfileboost.cpp
	Ver. k09.00
	
	Written by Koji Yamamoto
	Copyright (C) 2013-2019 Koji Yamamoto
	
	File System Utilities
	Using Boost.Filesystem
	
	TODO:
	using namespace stdをグローバルにはしない。
	
*/


/* ********** Preprocessor Directives ********** */

#ifndef kfileboost_cpp_include_guard
#define kfileboost_cpp_include_guard

#include <string>
#include <boost/filesystem.hpp>
#include <k09/kutil00.cpp>


/* ********** Using Directives ********** */

using namespace std;
using namespace boost :: filesystem;


/* ********** Type Declarations: enum, class, etc. ********** */


/* ********** Function Declarations ********** */

bool fileExists( const string &);
bool directoryOfFileExists( const string &);
void getCurrentDir( string &);
void getDirectoryOfFile( string &, const string &);
bool isFileNameWithFullPath( const string &);
void getTempFileName( string &, const string &, const string &, int);


/* ********** Type Definitions: enum, class, etc. ********** */


/* ********** Global Variables ********** */


/* ********** Definitions of Static Member Variables ********** */


/* ********** Function Definitions ********** */

/*
	Returns true if file named fn exists
*/
bool fileExists( const string &fn)
{
	
	path p( fn);
	return exists( p);
	
}

/*
	Returns true if the directory of the file named fn exists
*/
bool directoryOfFileExists( const string &fn)
{
	
	path p( fn);
	path dir = p.parent_path();
	return exists( dir);
	
}

/*
	Returns the current path into ret.
	e.g. ret = "c:\\cpp"
*/
void getCurrentDir( string &ret)
{
	
	path p;
	p = current_path();
	ret.assign( p.string());
	
}

/*
	Returns the directory name of the file named "fn" into ret.
	Example: If fn is
	 "C:\\cpp\\utilcraft\\temp.txt",
	then ret will be
	 "C:\\cpp\\utilcraft"
*/
void getDirectoryOfFile( string &ret, const string &fn)
{
	
	path p( fn);
	
	if ( exists( p) == false){
		alert( "getDirectoryOfFile()");
		ret.clear();
		return;
	}
	
	ret = p.parent_path().string();
	
}

/*
	Returns true if the file named "fn" is a file name and also contains full-path..
*/
bool isFileNameWithFullPath( const string &fn)
{
	
	path p( fn);
	
	if ( p.is_absolute() == true && p.has_filename() == true){
		return true;
	}
	
	return false;
	
}

/*
	利用可能な一時ファイル名を探し、結果をretに入れる。
	fn + （k桁の整数） + "." + （拡張子ext）というファイル名で、
	整数を増やしながら利用可能なものを探して返す。
	例：　        fn  = "c:\\cpp\\test\\tempf"
	              ext = "txt"
	              k   = 4
	返り値の例：　"c:\\cpp\\test\\tempf0019.txt"
*/
void getTempFileName( string &ret, const string &fn, const string &ext, int k)
{
	
	int count;
	string fn2, full;
	
	if ( k <= 0){
		alert( "getTempFileName()");
		ret.assign( "");
		return;
	}
	
	count = 0;
	do {
		fn2.clear();
		intToString( fn2, count, k);
		full = fn + fn2 + "." + ext;
		count++;
	} while ( fileExists( full));
	
	if ( count >= pow( 10.0, k)){
		alert( "getTempFileName()");
		ret.assign( "");
	}
	
	ret.assign( full);
	
}

/* ********** Definitions of Member Functions ********** */


#endif /* kfileboost_cpp_include_guard */
