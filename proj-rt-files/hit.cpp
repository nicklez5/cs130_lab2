#include "hit.h"
#include "object.h"

vec3 Hit::Normal() const
{
    vec3 xyz = location.normalized();
    return xyz;
}
