#ifndef __BOOLEAN_H__
#define __BOOLEAN_H__

#include "object.h"
#include <vector>
#include <set>
class Boolean : public Object
{
public:
    enum Type {type_intersection,type_difference,type_union} type;
    Object* A;
    Object* B;

    Boolean(Object* a, Object* b, Type t)
        :type(t),A(a),B(b)
    {
    }

    virtual void Intersection(const Ray& ray, std::vector<Hit>& hits) const override;
    virtual vec3 Normal(const vec3& point) const override;
    virtual void Update_Bounding_Box() override;
};
#endif
