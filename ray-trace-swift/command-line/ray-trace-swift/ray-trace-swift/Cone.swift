//
//  Cone.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/27/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct cone : hitable {
    let base: vec3_extend
    let base_radius: Float
    let apex: vec3_extend
    let apex_radius: Float
    let material: material
    
    init(_ base: vec3_extend, _ base_radius: Float, _ apex: vec3_extend, _ apex_radius: Float, _ material: material ) {
        self.base = base
        self.base_radius = base_radius
        self.apex = apex
        self.apex_radius = apex_radius
        self.material = material
    }
    
    func hit(_ r: ray, _ min: Float, _ max: Float, _ rec: inout hit_record) -> Bool {
        //t TODO
        return false
    }
    
    
}

