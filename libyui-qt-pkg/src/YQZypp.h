/*
  Copyright (C) 2000 - 2010 Novell, Inc.
  Copyright (c) 2021 SUSE LLC

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/


/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:		YQZypp.h

  Author:	Stefan Hundhammer <shundhammer.de>

/-*/


#ifndef YQZypp_h
#define YQZypp_h

#include <set>
#include <zypp/ui/Status.h>
#include <zypp/ui/Selectable.h>
#include <zypp/ResObject.h>
#include <zypp/Package.h>
#include <zypp/Pattern.h>
#include <zypp/Patch.h>
#include <zypp/Product.h>
#include <zypp/ZYppFactory.h>
#include <zypp/ResPoolProxy.h>


using zypp::ui::S_Protected;
using zypp::ui::S_Taboo;
using zypp::ui::S_Del;
using zypp::ui::S_Update;
using zypp::ui::S_Install;
using zypp::ui::S_AutoDel;
using zypp::ui::S_AutoUpdate;
using zypp::ui::S_AutoInstall;
using zypp::ui::S_KeepInstalled;
using zypp::ui::S_NoInst;


//
// Typedefs to make those nested namespaces human-readable
//

typedef zypp::ui::Status			ZyppStatus;
typedef zypp::ui::Selectable::Ptr		ZyppSel;
typedef zypp::ResObject::constPtr		ZyppObj;
typedef zypp::Package::constPtr			ZyppPkg;
typedef zypp::Pattern::constPtr			ZyppPattern;
typedef zypp::Patch::constPtr			ZyppPatch;
typedef zypp::Product::constPtr			ZyppProduct;
typedef zypp::PoolItem       			ZyppPoolItem;

typedef zypp::ResPoolProxy			ZyppPool;
typedef zypp::ResPoolProxy::const_iterator	ZyppPoolIterator;
typedef zypp::ResPoolProxy::repository_iterator	ZyppRepositoryIterator;

inline ZyppPool		zyppPool()		{ return zypp::getZYpp()->poolProxy();	}

template<class T> ZyppPoolIterator zyppBegin()	{ return zyppPool().byKindBegin<T>();	}
template<class T> ZyppPoolIterator zyppEnd()	{ return zyppPool().byKindEnd<T>();	}

inline ZyppPoolIterator zyppPkgBegin()		{ return zyppBegin<zypp::Package>();	}
inline ZyppPoolIterator zyppPkgEnd()		{ return zyppEnd<zypp::Package>();	}

inline ZyppPoolIterator zyppPatternsBegin()	{ return zyppBegin<zypp::Pattern>();	}
inline ZyppPoolIterator zyppPatternsEnd()	{ return zyppEnd<zypp::Pattern>();	}

inline ZyppPoolIterator zyppPatchesBegin()	{ return zyppBegin<zypp::Patch>();	}
inline ZyppPoolIterator zyppPatchesEnd()	{ return zyppEnd<zypp::Patch>();	}

inline ZyppPoolIterator zyppProductsBegin()	{ return zyppBegin<zypp::Product>();	}
inline ZyppPoolIterator zyppProductsEnd()	{ return zyppEnd<zypp::Product>();	}

inline ZyppRepositoryIterator ZyppRepositoriesBegin() { return zyppPool().knownRepositoriesBegin(); }
inline ZyppRepositoryIterator ZyppRepositoriesEnd()   { return zyppPool().knownRepositoriesEnd();   }

inline ZyppPkg		tryCastToZyppPkg( ZyppObj zyppObj )
{
    return zypp::dynamic_pointer_cast<const zypp::Package>( zyppObj );
}

inline ZyppPattern 	tryCastToZyppPattern( ZyppObj zyppObj )
{
    return zypp::dynamic_pointer_cast<const zypp::Pattern>( zyppObj );
}

inline ZyppPatch	tryCastToZyppPatch( ZyppObj zyppObj )
{
    return zypp::dynamic_pointer_cast<const zypp::Patch>( zyppObj );
}

inline ZyppProduct	tryCastToZyppProduct( ZyppObj zyppObj )
{
    return zypp::dynamic_pointer_cast<const zypp::Product>( zyppObj );
}


template<typename T> bool contains( const std::set<T> & container, T search )
{
    return container.find( search ) != container.end();
}


template<typename T> bool bsearch( const std::vector<T> & sorted_vector, T search )
{
    return binary_search( sorted_vector.begin(), sorted_vector.end(), search);
}


#endif // YQZypp_h
