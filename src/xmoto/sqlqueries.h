// this file is generated automatically by "xmoto --buildQueries", don't edit it
#define QUERY_LVL_ALL                                                        \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "         \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "           \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "          \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE (b.crappy " \
  "IS NULL OR xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL " \
  "OR xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS "  \
  "NULL"
#define QUERY_LVL_MY                                                         \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "         \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "           \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "          \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE (b.crappy " \
  "IS NULL OR xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL " \
  "OR xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS "  \
  "NULL AND a.isToReload = 1"
#define QUERY_LVL_FAVORITES                                             \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "    \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "      \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "     \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) INNER JOIN " \
  "levels_favorite AS d ON (a.id_level = d.id_level AND "               \
  "d.id_profile=xm_profile()) AND (b.children_compliant IS NULL OR "    \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL"
#define QUERY_LVL_BLACKLIST                                                  \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "         \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "           \
  "a.id_level=b.id_level INNER JOIN levels_blacklist AS c ON (a.id_level = " \
  "c.id_level AND c.id_profile=xm_profile()) WHERE (b.crappy IS NULL OR "    \
  "xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL OR "         \
  "xm_userChildrenCompliant(b.children_compliant)=1)"
#define QUERY_LVL_SCRIPTED                                                   \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "         \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "           \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "          \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE (b.crappy " \
  "IS NULL OR xm_userCrappy(b.crappy)=0) AND a.isScripted=1 AND "            \
  "(b.children_compliant IS NULL OR "                                        \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL"
#define QUERY_LVL_PHYSICS                                                    \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "         \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "           \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "          \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE (b.crappy " \
  "IS NULL OR xm_userCrappy(b.crappy)=0) AND a.isPhysics=1 AND "             \
  "(b.children_compliant IS NULL OR "                                        \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL"
#define QUERY_LVL_INCOMPLETED                                                  \
  "SELECT a.id_level AS id_level, MIN(a.name) AS name, MIN(UPPER(a.name)) AS " \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "             \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "            \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) LEFT OUTER JOIN "   \
  "stats_profiles_levels AS e ON (a.id_level = e.id_level AND "                \
  "e.id_profile=xm_profile()) WHERE (b.crappy IS NULL OR "                     \
  "xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL OR "           \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL "  \
  "GROUP BY a.id_level, e.id_profile HAVING MAX(e.nbCompleted+0) = 0 OR "      \
  "MAX(e.nbCompleted+0) IS NULL"
#define QUERY_LVL_NEW                                                          \
  "SELECT a.id_level AS id_level, xm_lvlUpdatedToTxt(f.isAnUpdate) || \": \" " \
  "|| a.name AS name, UPPER(a.name) AS sort_field FROM levels AS a LEFT "      \
  "OUTER JOIN weblevels AS b ON a.id_level=b.id_level LEFT OUTER JOIN "        \
  "levels_blacklist AS c ON (a.id_level = c.id_level AND "                     \
  "c.id_profile=xm_profile()) INNER JOIN levels_new AS f ON a.id_level = "     \
  "f.id_level WHERE (b.crappy IS NULL OR xm_userCrappy(b.crappy)=0) AND "      \
  "(b.children_compliant IS NULL OR "                                          \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL"
#define QUERY_LVL_CRAPPY                                                      \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "          \
  "sort_field FROM levels AS a INNER JOIN weblevels AS b ON "                 \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "           \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE b.crappy=1 " \
  "AND xm_userChildrenCompliant(b.children_compliant)=1 AND c.id_level IS "   \
  "NULL"
#define QUERY_LVL_LAST                                                       \
  "SELECT a.id_level AS id_level, a.name AS name, b.creationDate AS "        \
  "sort_field FROM levels AS a INNER JOIN weblevels AS b ON "                \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "          \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) WHERE "           \
  "xm_userCrappy(b.crappy)=0 AND "                                           \
  "xm_userChildrenCompliant(b.children_compliant)=1 AND c.id_level IS NULL " \
  "ORDER BY b.creationDate DESC LIMIT 100"
#define QUERY_LVL_STOLEN                                                       \
  "SELECT a.id_level AS id_level, a.name AS name, g.known_stolen_date AS "     \
  "sort_field FROM levels AS a INNER JOIN levels_mywebhighscores AS g ON "     \
  "a.id_level = g.id_level INNER JOIN weblevels AS b ON "                      \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "            \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) LEFT OUTER JOIN "   \
  "webhighscores AS h     ON (    g.id_room    = h.id_room         AND "       \
  "g.id_level   = h.id_level         AND g.id_profile = h.id_profile) WHERE "  \
  "xm_userCrappy(b.crappy)=0 AND "                                             \
  "xm_userChildrenCompliant(b.children_compliant)=1 AND c.id_level IS NULL "   \
  "AND g.id_profile=xm_profile() AND g.id_room=xm_idRoom(0) AND h.id_profile " \
  "IS NULL"
#define QUERY_LVL_NO_HIGHSCORE                                                \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "          \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "            \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "           \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) LEFT OUTER JOIN "  \
  "webhighscores AS i     ON (    i.id_level   = a.id_level         AND "     \
  "i.id_room    = xm_idRoom(0)) WHERE (b.crappy IS NULL OR "                  \
  "xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL OR "          \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL " \
  "AND i.id_profile IS NULL"
#define QUERY_LVL_NOT_THE_HIGHSCORE                                           \
  "SELECT a.id_level AS id_level, a.name AS name, UPPER(a.name) AS "          \
  "sort_field FROM levels AS a LEFT OUTER JOIN weblevels AS b ON "            \
  "a.id_level=b.id_level LEFT OUTER JOIN levels_blacklist AS c ON "           \
  "(a.id_level = c.id_level AND c.id_profile=xm_profile()) INNER JOIN "       \
  "webhighscores AS i     ON (    i.id_level   = a.id_level         AND "     \
  "i.id_room    = xm_idRoom(0)) WHERE (b.crappy IS NULL OR "                  \
  "xm_userCrappy(b.crappy)=0) AND (b.children_compliant IS NULL OR "          \
  "xm_userChildrenCompliant(b.children_compliant)=1) AND c.id_level IS NULL " \
  "AND i.id_profile <> xm_profile()"
#define QUERY_LVL_LAST_HIGHSCORES                                              \
  "SELECT a.id_level AS id_level, a.name AS name, i.date AS sort_field FROM "  \
  "levels AS a LEFT OUTER JOIN weblevels AS b ON a.id_level=b.id_level LEFT "  \
  "OUTER JOIN levels_blacklist AS c ON (a.id_level = c.id_level AND "          \
  "c.id_profile=xm_profile()) INNER JOIN webhighscores AS i     ON (    "      \
  "i.id_level   = a.id_level         AND i.id_room    = xm_idRoom(0)) WHERE "  \
  "(b.crappy IS NULL OR xm_userCrappy(b.crappy)=0) AND (b.children_compliant " \
  "IS NULL OR xm_userChildrenCompliant(b.children_compliant)=1) AND "          \
  "c.id_level IS NULL ORDER BY i.date DESC LIMIT 100"
#define QUERY_LVL_OLDEST_HIGHSCORES                                            \
  "SELECT a.id_level AS id_level, a.name AS name, i.date AS sort_field FROM "  \
  "levels AS a LEFT OUTER JOIN weblevels AS b ON a.id_level=b.id_level LEFT "  \
  "OUTER JOIN levels_blacklist AS c ON (a.id_level = c.id_level AND "          \
  "c.id_profile=xm_profile()) INNER JOIN webhighscores AS i     ON (    "      \
  "i.id_level   = a.id_level         AND i.id_room    = xm_idRoom(0)) WHERE "  \
  "(b.crappy IS NULL OR xm_userCrappy(b.crappy)=0) AND (b.children_compliant " \
  "IS NULL OR xm_userChildrenCompliant(b.children_compliant)=1) AND "          \
  "c.id_level IS NULL ORDER BY i.date ASC LIMIT 100"
