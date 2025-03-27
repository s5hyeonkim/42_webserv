// import { create } from "zustand";
// import { CommentState } from "./Comment";
// // import { ExtractState } from "zustand";
// // import { create } from "zustand/middleware";

// interface UserState {
//   userId: number;
//   userName: string;
//   comments: CommentState[];
//   error: boolean;
//   isMine: boolean;
//   isLoading: boolean;
//   fetchUserId: () => Promise<void>;
// }

// const useUserStore = create<UserState>((set) => ({
//   userId: 0,
//   userName: "",
//   comments: [],
//   error: false,
//   isMine: false,
//   isLoading: false,
//   fetchUserId: async () => {
//     set({ isLoading: true });
//     try {
//       const { userId, timeZone } = get();
//       const res = await fetch("localhost:2424/comments", {
//         method: "POST",
//         headers: {
//           "Content-Type": "application/json",
//         },
//         body: JSON.stringify({
//           userId,
//           timeZone,
//         }),
//       });
//       if (!res.ok) throw new Error("Failed to send data");
//       const data = await res.json();
//       set({ isLoading: false, error: false });
//       console.log("Success:", data);
//     } catch (error) {
//       set({ isLoading: false, error: true });
//     }
//   },
// }));
