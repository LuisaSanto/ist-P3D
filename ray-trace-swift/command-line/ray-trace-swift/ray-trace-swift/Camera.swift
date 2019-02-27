//
//  Camera.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/26/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

import Foundation

struct Camera {
    let origin: vec3_extend
    let u, v, w: vec3_extend
    let vertical: vec3_extend
    let horizontal: vec3_extend
    let lower_left_corner: vec3_extend
    
    init(_ lookFrom: vec3_extend, _ lookAt: vec3_extend, _ vectorUp: vec3_extend,
         _ fov: Float, _ hither: Float, _ width: Float, height: Float ) {
        self.origin = lookFrom
        w = unit_vector(vector: lookFrom - lookAt)
        u = unit_vector(vector: cross_product(vectorUp, w))
        v = cross_product(w, u)
        
        let half_width = width / 2
        let half_height = height / 2
        
        self.lower_left_corner = origin - half_width*u - half_height*v - w
        self.horizontal = 2 * half_width * u
        self.vertical = 2 * half_height * v
    }
    
    func get_rays(_ source: Float, _ target: Float) -> ray {
        let ray_direction = lower_left_corner + source * horizontal + target * vertical - origin
        return ray(origin, ray_direction)
    }
}
