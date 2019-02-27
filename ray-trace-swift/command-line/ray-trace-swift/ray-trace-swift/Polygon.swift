//
//  Polygon.swift
//  ray-trace-swift
//
//  Created by Luisa Santo on 2/27/19.
//  Copyright © 2019 Luisa Santo. All rights reserved.
//

struct polygon : hitable {
    let total_faces: Int
    let faces: [vec3_extend]
    let material: material
    
    init(_ total_faces: Int, _ faces: [vec3_extend], _ material: material) {
        self.total_faces = total_faces
        self.faces = faces
        self.material = material
    }
    
    func hit(_ r: ray, _ min: Float, _ max: Float, _ rec: inout hit_record) -> Bool {
        // TODO
        return false
    }
    
    
}
