#ifndef DBDEFINES_H
#define DBDEFINES_H

#ifndef DBNETLIST_H
 class dbNetlist;
#endif


#ifndef MakeFriendsWithParsers
#define MakeFriendsWithParsers     friend class ParserBookShelf; \
/* 				friend int   defparse();    \
				friend class ParserLEFDEF;  \
				friend class ParserLEFDEFq; \
				friend class ParserXXX;     \  
				friend class putYourFavoriteParserHere; \
friend class AtomicChanges; \
friend class InsertDelete; \
friend void sortEqClasses(dbNetlist& design); \
friend void sortObstacles(dbNetlist& design); \
friend void sortPins(dbNetlist& design); // workaround for CC iropt bug 
*/
#endif 


#endif 