import { create } from "zustand";
// import { useQuery } from "@tanstack/react-query";

export interface User {
  user_id: number;
  user_name: string;
  // setUser: (id: UserStore["id"], name: UserStore["name"]) => void;
}

export interface UserStore {
  user: User | null;
  // setUser: (users: User) => void;
  setUser: (users: User) => void;
  users: User[];
  setUsers: (users: User[]) => void;
  newUsers: User[];
  setNewUsers: (users: User[]) => void;
  deletedUsers: User[];
  setDeletedUsers: (users: User[]) => void;
  // deleteUser: (id: number) => void;
}

export const useUserStore = create<UserStore>((set) => ({
  user: null,
  setUser: (user) => set({ user: user }),
  users: [],
  setUsers: (users) => set({ users: users }),
  newUsers: [],
  setNewUsers: (users) => set({ newUsers: users }),
  deletedUsers: [],
  setDeletedUsers: (users) => set({ deletedUsers: users }),
}));
