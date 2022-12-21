import { Socket } from 'net';

export type ControllerResponse<T> = {
    message?: string;
    data?: T | T[] | Record<any, any> | null;
    error?: string;
};

export type Product = {
    id: number;
    name: string;
    price: number;
    image: string;
};

type Order = {
    [x: string]: any;
    id?: string;
    client?: Socket;
    deliver_man?: string;
    price: number;
    items: string[];
    status?: string;
    change?: number;
};

type Client = {
    name?: string;
    uuid?: string;
    status?: {
        currentVelocity: string;
        crashVelocity: string;
        isHonking: string;
        highestVelocity: string;
        targetDistance: string;
        timestamp: string;
    }
};

// export type Delivery = {
//   id: number;
//   type: string;
//   product: Product;
//   payment_type: string;
//   costumer: Costumer;
//   deliveryman: string;
// };
