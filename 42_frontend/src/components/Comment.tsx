// import { create } from "zustand";
// // import { ExtractState } from "zustand";
// // import { create } from "zustand/middleware";

// export interface CommentState {
//   userId: number;
//   userName: string;
//   commentsId: number;
//   content: string;
//   timeZone: string;
//   isLoading: boolean;
//   error: boolean;
//   isMine: boolean;
//   // setTimeZone: (TimeZone: string) => void;
//   setUserId: (UserId: number) => void;
//   setCommentsId: () => Promise<void>;
// }

// // type CommentState = ExtractState<typeof useCommentStore>

// const useCommentStore = create<CommentState>((set) => ({
//   userId: 0,
//   commentsId: 0,
//   userName: "",
//   timeZone: "",
//   content: "",
//   isLoading: false,
//   error: false,
//   isMine: false,
//   setUserId: (userId: number) => set({ userId }),
//   setCommentsId: async () => {
//     set({ isLoading: true });
//     try {
//       const { userId, timeZone } = useCommentStore.getState();
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
//   // increase: (by) => set((state)=> ({commentsId: state.commentId + by})),
// }));

// // const useCommentStore = create(
// //     combine ({ commentsId: 0 }, (set) => ({
// //         increase: (by: number) => set((state)=> ({commentsId: state.commentId + by})),
// //     })),
// // )

// // export default useCommentStore;
