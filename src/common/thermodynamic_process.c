/*
 Thermodynamic process
*/
#include "common.h"
#include "constand.h"
#include "propertry_id.h"
#include "seuif97.h"

IF97_DLL double seuishd(double pi, double ti, double pe)
{
   double hi, si, he_isos;
   if (pi <= pe)
      return INVALID_VALUE;

   hi = seupt(pi, ti, OH);
   if (hi <= 0)
      return INVALID_VALUE;

   si = seupt(pi, ti, OS);
   if (si < -500)
      return INVALID_VALUE;

   he_isos = seups(pe, si, OH);
   if (he_isos < 0)
      return INVALID_VALUE;

   return (hi - he_isos);
}

// superheated steam zone , %
IF97_DLL double seuief(double pi, double ti, double pe, double te)
{
   double hi, si, he_isos, he, se, ishd, ahd;
   if (pi <= pe)
      return INVALID_VALUE;
   if (ti <= te)
      return INVALID_VALUE;

   hi = seupt(pi, ti, OH);
   if (hi < -500)
      return INVALID_VALUE;

   si = seupt(pi, ti, OS);
   if (si < -500)
      return INVALID_VALUE;

   he_isos = seups(pe, si, OH);
   if (he_isos < -500)
      return INVALID_VALUE;
   ishd = (hi - he_isos);

   he = seupt(pe, te, OH);
   if (he < -500)
      return INVALID_VALUE;
   se = seupt(pe, te, OS);
   if (se < -1000)
      return INVALID_VALUE;

   if ((se - si) <= 0)
      return INVALID_VALUE;

   ahd = (hi - he);
   return (100.0 * ahd / ishd);
}
