//
//  Sphere.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/27/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct sphere : hitable {
    let center: vec3_extend
    let radius: Float
    let material: material
    
    init(_ center: vec3_extend, _ radius: Float, _ material: material ) {
        self.center = center
        self.radius = radius
        self.material = material
    }
    
    func hit(_ r: ray, _ min: Float, _ max: Float, _ rec: inout hit_record) -> Bool {
        //t TODO
        return false
    }
    
    
}
